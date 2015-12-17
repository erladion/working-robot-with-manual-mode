/*
 * BusSlave.c
 *
 * Created: 11/30/2015 4:06:27 PM
 *  Author: filma035
 */ 

#include <avr/interrupt.h>
#include "BusSlave.h"
//#include <util/twi.h>
#include "DebugHelp.h"


ISR(TWI_vect){
	// SEND DATA - sensormodul
	pulse(PORTC, 7);
	// The Slave has been addressed by the Master
	if ((TWSR & 0xF8) == 0xA8){ // use TW_ST_DATA_ACK instead of 0xA8 maybe?
		sending = 1;
		pulse(PORTD,0);
		TWIcounter = 0;
		TWDR = TWIdata[TWIcounter];
		TWIcounter++;
		TWCR = (1 << TWINT) | (1 << TWEA) | (1 << TWIE) | (1 << TWEN);
	}
	// Send data now
	else if ((TWSR & 0xF8) == 0xB8){
		pulse(PORTC, 7);
		pulse(PORTC, 7);
		TWDR = TWIdata[TWIcounter];
		TWIcounter++;
		TWCR = (1<< TWINT) | (1 << TWEA) | (1 << TWIE) | (1 << TWEN);
	}
	// Done with sending data
	else if ((TWSR & 0xF8) == 0xC0){
		sending = 0;
		TWCR = (1<< TWINT) | (1 << TWEA) | (1 << TWIE) | (1 << TWEN);		
	}
	
	//RECEIVE DATA - styrmodul
	
	// The Slave has been addressed by the Master
	else if ((TWSR & 0xF8) == 0x60){
		TWCR = (1<< TWINT) | (1 << TWEA) | (1 << TWIE) | (1 << TWEN);
		calibrateReflexSensors();
		TWIcounter = 0;
	}
	
	// Data is received
	else if ((TWSR & 0xF8) == 0x80){	
		TWCR = (1<< TWINT) | (1 << TWEA) | (1 << TWIE) | (1 << TWEN);
	}
	
	// STOP condition is received
	else if ((TWSR & 0xF8) == 0xA0){
		TWCR = (1<< TWINT) | (1 << TWEA) | (1 << TWIE) | (1 << TWEN);
	}
	else{
		sending = 0;
	}
}

void initBuss(char address){
	DDRC |= (1 << 7);
	DDRD |= (1 << 0);
	//pulse(PORTC, 7);
	sending = 0;
	
	TWAR = address;
	TWCR = (1 << TWEN) | (1 << TWEA) | (1 << TWIE); // set the TWCR to enable address matching and enable TWI, enable TWI interrupt
	TWCR |= (1 << TWINT); // clear TWINT
	cbi(TWCR, TWSTA);
	cbi(TWCR, TWSTO);
	//pulse(PORTC, 7);
}