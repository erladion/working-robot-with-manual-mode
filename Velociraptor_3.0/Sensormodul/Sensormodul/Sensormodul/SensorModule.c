/*
 * SensorModule.c
 *
 * Created: 12/1/2015 9:34:34 AM
 *  Author: filma035
 */
//#define F_CPU (16000000UL)
#include <avr/interrupt.h>
#include <avr/delay.h>
#include <stdbool.h>
#include "IRSensor.h"
#include "UltrasoundSensor.h"
#include "Display.h"
#include "BusSlave.h"
#include "Gyro.h"
#include "DebugHelp.h"
#include "PDController.h"
#include "SensorAlgorithm.h"
#include "Reflexsensormodul.h"

bool startButton;
int reflex;
volatile int mode; 

void combineData(){
	// We send 2 empty bytes to make sure we dont lose any real data
	TWIdata[0] = 0x00;
	TWIdata[1] = 0x00;
	TWIdata[2] = (1<<7) | (startButton << 6) | ( 1 < mode);
	TWIdata[3] = (reflex_data >> 8);
	TWIdata[4] = reflex_data;
	TWIdata[5] = ((int)currentAngle >> 8);
	TWIdata[6] = (int)currentAngle;
	TWIdata[7] = ((int)distanceFront >> 8);
	TWIdata[8] = (int)distanceFront;
	TWIdata[9] = ((int)distanceBack >> 8);
	TWIdata[10] = (int)distanceBack;
	TWIdata[11] = IRFR;
	TWIdata[12] = IRFL;
	TWIdata[13] = IRBR;
	TWIdata[14] = IRBL;
	TWIdata[15] = 0;
	TWIdata[16] = 0;
}

// Interrupt that occurs everytime we press the startbutton
ISR(PCINT1_vect){
	// We XOR to just switch between true and false
	if (bit_is_set(PINB,7)){
		startButton ^= true;
	}
}

// Initiate the startbutton
void startButtonInit(){
	DDRB &= ~(1<<PB7);
	// Enables external interrupt on PB7
	PCMSK1 |= (1 << PCINT15); 
	PCICR |= (1 << PCIE1);			
}

int main(void){
	_delay_ms(10000); // Gives time for everything to start up before we init.
	startButton = false;
	mode = false;
	int modeArray[8];
	irInit();	
	lcd_init();
	gyroInit();	
	initBuss(0b00000100);
	ultrasoundInit();
	reflex_init();
	startButtonInit();
	combineData();
	getBias();
	sei();
	DDRC |= (1 << 7); // Set PC7 as output for testing
	DDRB |= (1 << 0);
	while(1){
		// Check if the modeswitch pin is set or not to indicate which mode we are in
		// mode 1 = manual
		// mode 0 = autonom
		if (bit_is_set(PINB, 0)){
			mode = 1;
		}
		else{
			mode = 0;
		}
				
		_delay_ms(10);
		// Read all the ir sensors
		readAllIr();
		// Make a read on all of the reflexsensors
		reflex_run_all();
		
		// OBS: If this while is used, it doesn't take a lot of time for the data on the bus from the sensor module to the communications module to transfer and everything works properly for a while until it stops.
		// OBS: If it is not used, it takes a lot of time for the data on the bus from the sensor module to the communications module to transfer. But everything else works properly.
		//while(sending); //wait with turning off interrupts until we are done sending data
		
		// OBS! ULTRA SOUND WORKS WORSE WHEN YOU USE CLI AND SEI
		cli();
		// Update the lcd-display
		lcd_update(mode,reflexValue1,reflexValues[1], reflexValues[2],IRFL, IRFR, IRBL, IRBR);
		// Set the correct sensordata to each byte we send out on the bus
		combineData();
		sei();		
	}
}
