
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sfr_defs.h>
#include <avr/delay.h>
#include "bluetooth.h"
#include "Buss.h"

#define sbi(port,bit) (port) |= (1 << (bit))
#define cbi(port,bit) (port) &= ~(1 << (bit))

#define pulse(port,bit) cbi(port,bit); sbi(port,bit); cbi(port,bit)

#define F_CPU 14745000UL

#define USART_BAUDRATE 115200
#define BAUD_PRESCALE (((14745000 / (USART_BAUDRATE * 16UL))) - 1)

volatile int bitAr[8];

ISR(USART0_RX_vect){
	command = USARTReadChar();	
	speed = USARTReadChar();
	turnrate = USARTReadChar();
	
	bluetoothData[1] = command;
	bluetoothData[2] = speed;
	bluetoothData[3] = turnrate;
}

void makeBitArray(int array[], int val){
	for (int i = 0; i < 8; i++)
	{
		array[i] = val & (1 << i) ? 1 : 0;
	}
}

//This function is used to read the available data
//from USART. This function will wait until data is
//available.
unsigned char USARTReadChar(void) {
	//Wait until a data is available
	loop_until_bit_is_set(UCSR0A, RXC0);
	/*while(!(UCSR0A & (1<<RXC0)))
	{
		//Do nothing
	}*/	

	//Now USART has got data from host
	//and is available is buffer
	return UDR0;
}

// Sends back the data that we recieved, used for debugging
void sendBackCommand(){	
	UART_TxChar(command);
	UART_TxChar(speed);
	UART_TxChar(turnrate);
	UART_TxChar('\n');	
}

void UART_TxChar(unsigned char data)
{
	//pulse(PORTB, 0);
	while(!(UCSR0A & (1<<UDRE0)));
	UDR0 = data;
}
 
void UART_TxStr(char *str, int length)
{
	//pulse(PORTB, 1);
    int a=0;
    while(a != length){
		UART_TxChar(str[a++]);
	}
    UART_TxChar('\n');
}

void initBluetooth(){
	
	//cbi(DDRD,PD0);
	//sbi(DDRD,PD1);
	//DDRD = 0x00;
	
	bluetoothData[0] = 48;
	bluetoothData[1] = 48;
	bluetoothData[2] = 48;
	
	// Enable RX, TX and interupts for RX
	UCSR0B= (1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0);
	
	// Set 8-bit data size
	sbi(UCSR0C, UCSZ00);
	sbi(UCSR0C, UCSZ01);	
	
	// Set 1 stopbit
	cbi(UCSR0C, USBS0);
	
	// Mode (00 = ASYNC, 01 = SYNC, 10 = nothing, 11 = Master SPI)
	cbi(UCSR0C, UMSEL00);
	cbi(UCSR0C, UMSEL01);
	
	
	cbi(UCSR0A,U2X0);
	//UCSR0C= (3<<UCSZ00); // 8 bit
	
	// Set UBRR
	//UBRR0L = BAUD_PRESCALE; 
	//UBRR0H = (BAUD_PRESCALE >> 8); 
	UBRR0H = 0x00;
	UBRR0L = 0x07;
}
