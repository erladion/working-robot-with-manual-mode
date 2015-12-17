/*
 * BusSlave.c
 *
 * Created: 11/30/2015 4:06:27 PM
 *  Author: filma035
 */ 

#include <avr/interrupt.h>
#include "BusSlave.h"
#include "DebugHelp.h"
#include "BusValues.h"
ISR(TWI_vect){
	// SEND DATA - sensormodul
	
	// The Slave has been addressed by the Master
	if ((TWSR & 0xF8) == 0xA8){
		TWIcounter = 0;
		TWDR = TWIdata[TWIcounter];
		TWCR = (1<< TWINT) | (1 << TWEA) | (1 << TWIE) | (1 << TWEN);
	}
	// Send data now
	if ((TWSR & 0xF8) == 0xB8){
		TWDR = TWIdata[TWIcounter];
		TWIcounter++;
		TWCR = (1<< TWINT) | (1 << TWEA) | (1 << TWIE) | (1 << TWEN);
	}
	// Done with sending data
	if ((TWSR & 0xF8) == 0xC0){
		TWCR = (1<< TWINT) | (1 << TWEA) | (1 << TWIE) | (1 << TWEN);
	}
	
	//RECEIVE DATA - styrmodul
	
	// The Slave has been addressed by the Master
	if ((TWSR & 0xF8) == 0x60){
		TWCR = (1<< TWINT) | (1 << TWEA) | (1 << TWIE) | (1 << TWEN);
		TWIcounter = 0;
	}
	
	// Data is received
	if ((TWSR & 0xF8) == 0x80){
		char var = TWDR;
		if (TWIcounter <4){
			//if (TWIcounter == 0){
				//if (var != 0){
					//mode = 1;
				//}
				//else{
					//mode = 0;
				//}
			//}
		if (mode)
			TWIdata[TWIcounter] = var;
		 } else {
			updateBusValues(var,TWIcounter); // Saves the latest sensor data from the bus.
		 }
		TWIcounter++;
		TWCR = (1<< TWINT) | (1 << TWEA) | (1 << TWIE) | (1 << TWEN);
	}
	
	// STOP condition is received
	if ((TWSR & 0xF8) == 0xA0){		
		TWCR = (1<< TWINT) | (1 << TWEA) | (1 << TWIE) | (1 << TWEN);
	}
}

void initBuss(char address){
	TWAR = address;
	TWCR = (1 << TWEN) | (1 << TWEA) | (1 << TWIE) | (1 << TWINT);
	//TWBR = 0x08;
	sensor = 0;
}