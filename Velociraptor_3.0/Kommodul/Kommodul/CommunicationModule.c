/*
 * CommunicationModule.c
 *
 * Created: 12/1/2015 10:43:50 AM
 *  Author: filma035
 */ 
#define F_CPU 14700000UL
#include <avr/interrupt.h>
#include <avr/delay.h>
#include "Buss.h"
#include "bluetooth.h"

int sendCounter = 40;


int main(void){
	initBluetooth();
	initBuss();
	//_delay_ms(100); // What does this do?
	sei(); //Enable global interrupts
	
	DDRB |= 0b01111111;	
	
	while(1){
		if (bit_is_set(PINB, 0)){
			manualMode = 1;
		}
		else{
			manualMode = 0;
		}
		readData(0b00000100); // Read data from the sensor module
		_delay_ms(50);
		// Check if the switch is set to manual mode or not
		//manualMode = ((sensorData[2] & (1 << 3)) >> 3); 
		
		// If the switch is set to manual mode, send the sensor data to the steering module. 
		//Otherwise, send the bluetooth data to the steering module.
		if (manualMode == 0){
			sendData(0b00000010,sensorData,15);
		}
		else{
			// If we get a command to calibrate the tape sensor, send a command to the sensor module, otherwise to the steering module
			if (bluetoothData[0] == '7'){
				sendData(0b00000100,0x01,1);
				bluetoothData[0] = '0';
			}
			else {				
				bluetoothData[0] = (1 << 3);//sensorData[2];
				sendData(0b00000010,bluetoothData,4);
			}
		}
		_delay_ms(10);		
	}
}