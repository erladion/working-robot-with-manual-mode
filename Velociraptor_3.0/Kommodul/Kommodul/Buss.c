/*
 * Buss.c
 *
 * Created: 11/17/2015 9:36:52 AM
 *  Author: filma035
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include <avr/delay.h>
#include <stdio.h>
#include <string.h>
#include "bluetooth.h"
#include "Buss.h"

#define sbi(port,bit) (port) |= (1 << (bit))
#define cbi(port,bit) (port) &= ~(1 << (bit))

#define pulse(port,bit) cbi(port,bit); sbi(port,bit); cbi(port,bit)

#define STARTTRANSMITTED 0x08
#define SLAWTRANSMITTED 0x18
#define DATATRANSMITTED 0x28

#define SLARTRANSMITTED 0x40
#define DATARECEIVED 0x50
#define RECEIVECOMPLETE 0x58

#define STARTCONDITION (1<<TWINT)|(1<<TWSTA)|(1<<TWEN) |(1 << TWIE)
#define SEND (1<<TWINT) | (1<<TWEN)|(1 << TWIE)
#define RECEIVE (1<<TWINT) | (1<<TWEN)|(1 << TWIE) | (1 << TWEA)
#define STOP (1<<TWINT)|(1<<TWEN)|(1<<TWSTO)|(1 << TWIE)
#define STOPSENDING (1<<TWINT)|(1 << TWIE) | (1 << TWEN)

#define INITBUSS (1 << TWIE) | (1 << TWEN)

volatile char* TWIdata;
volatile char TWIaddress;
volatile int TWIlength;
volatile int TWIcounter;

volatile int bluetoothCounter;

volatile bool sending;

ISR(TWI_vect){
	switch (TWSR & 0xF8){
	// START condition has been transmitted
	case STARTTRANSMITTED:
		TWDR = TWIaddress;
		TWCR = SEND;
		break;	
		
	case SLAWTRANSMITTED:
		TWDR = TWIdata[TWIcounter];
		TWIcounter++;
		TWCR = SEND;
		break;
	
	// Data has been sent
	case DATATRANSMITTED:
		// IF we haven't sent all data, keep sending
		if (TWIcounter < TWIlength){
			TWDR = TWIdata[TWIcounter];
			TWIcounter++;
			TWCR = SEND;	
		}
		else {
			//Transmit STOP condition
			TWCR = STOP;
			sending = false;
		}
		break;
	
	// SLA+R transmitted
	case SLARTRANSMITTED:
		TWCR = RECEIVE;
		break;
	
	// Data has been received
	case DATARECEIVED:
		sensorData[TWIcounter] = TWDR;
		UART_TxChar(sensorData[TWIcounter]);				
		TWIcounter++;
		if (TWIcounter < TWIlength){
			TWCR = RECEIVE;
		}
		else{
			TWCR = STOPSENDING;	
			UART_TxChar('\n');
		}		
		break;	
	
	case RECEIVECOMPLETE:
		//Transmit STOP condition
		TWCR = STOP;
		break;
	default: // If something goes wrong, we stop.
		if (TWIcounter > 0) UART_TxChar('\n');
		TWCR = STOP;
		break;
	}	
}

void initBuss(){
	bluetoothCounter = 0;
	
	TWCR = INITBUSS; //Enable bus
	TWCR |= (1<<TWINT);
	
	/*
	The clock frequency for the I2C bus should be 100 kHz.
	It is calculated with this formula:
	
	Bus_frequency	= Clock_frequency / (16 + 2(TWBR) * 4^TWPS)
					= / TWBR = 16 and TWPS = 1/ =
					= 14700000 / (16 + 2(16) * 4^1)
					=~ 100 kHz	
		
	TWPS1	TWPS1	Prescaler_value
	0		0		1
	0		1		4
	1		0		16
	1		1		64
	*/	
	TWSR &= ~(1 << TWPS0); // Set TWPS0 = 0
	TWSR &= ~(1 << TWPS1); // Set TWPS1 = 0	
	sending = false;
	TWBR = 16;
}

void sendData(char address, char* data, int datalength){
	TWIaddress = address & 0xFE; // Sets the read/write bit (the 8th bit) to 0 which creates a write call
	TWIdata = data;
	TWIlength = datalength;
	TWIcounter = 0;		
	
	//Send a START condition to the TWI
	TWCR = STARTCONDITION;	
}


void readData(char address){	
	TWIaddress = address | 1; // Sets the read/write bit (the 8th bit) to 1 which creates a read call	
	TWIcounter = 0;
	TWIlength = 16; // The number of bytes that will be received from the sensor module
	
	//Send a START condition to the TWI
	TWCR = STARTCONDITION;	
}
