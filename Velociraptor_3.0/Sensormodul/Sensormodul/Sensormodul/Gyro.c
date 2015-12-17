/*
 * Gyro.c
 *
 * Created: 11/20/2015 11:00:42 AM
 *  Author: johja118
 */ 


#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <avr/interrupt.h>
#include <math.h>
#include "Gyro.h"
#include "DebugHelp.h"
#include "avr/delay.h"


int gyroADCValue;
int angleArray[10];
volatile float currentAngle = 0;

// Constant calculated from testing
float gain = 0.65;
// Integration time (10ms)
float gyrotime = 0.01;
const float angleThreshold = 10;

int i;
/*
 * Reads the current output value from the gyro and returns it
 *
 */
uint16_t adcGyro(){
	// Select which channel to make the ADC (Analog-digital converter) read on, since the gyro is connected to PA4 make a read on port 4.
	// The three bits MUX2-MUX0 selects which channel to read from where MUX2 is MSB and MUX0 is LSB
	// Clear MUX3 so no overflow occurs since sbi uses or.		
	cbi(ADMUX, MUX3);
	sbi(ADMUX, MUX2);
	cbi(ADMUX, MUX1);
	cbi(ADMUX, MUX0);
	
	// For the ADC to give reliable output we have to make an extra read every time we change channel.
	//(We are also using IR-sensors which need the ADC so we have to do this extra read every time we want a value from the gyro)
	// This read is useless, see AVRs documentation for analog-digital converter.	
	sbi(ADCSRA, ADSC);
	loop_until_bit_is_clear(ADCSRA, ADSC);
		
	// Reads the current output from the gyro
	sbi(ADCSRA, ADSC);
	loop_until_bit_is_clear(ADCSRA, ADSC);
	
	// Since the ad converted value is saved in 2 8-bit registers
	// we have to read the first 8 low bits to not corrupt the read.
	int low = ADCL;
	
	// Shift the 2 high bits 8 steps, and then add the low bits 
	return (ADCH << 8) | low;
}

void adcInit(){
	// Set the reference voltage to AVCC, 5V
	sbi(ADMUX, REFS0);
	cbi(ADMUX, REFS1);
	
	// Disable the digital input buffer
	DIDR0 = 0x0F;
	
	// Enable the ADC
	sbi(ADCSRA, ADEN);	
	
	// For the AD-converting to give an accurate value the ADC clock has to be run
	// between 50 and 200kHZ, since we run a 16MHz clock we have to set the prescalar to 128,
	// which gives us a clock of 125kHz while a prescalar of 64 would give 250kHz
	// Set prescalar to 128
	//  ADPS2	ADPS1	ADPS0
	//		0		0		0	2
	//		0		0		1	2
	//		0		1		0	4
	//		0		1		1	8
	//		1		0		0	16
	//		1		0		1	32
	//		1		1		0	64
	//		1		1		1	128
	sbi(ADCSRA,ADPS0);
	sbi(ADCSRA,ADPS1);
	sbi(ADCSRA,ADPS2);
}


ISR(TIMER2_COMPA_vect){	
	// Read the current output from the ADC
	gyroADCValue = adcGyro();
	
	// Calculate the difference in the newly read value and the one read at the start
	int val = gyroADCValue - defaultAngle;	
	
	// Since the ADC doesn't give the same value every time even while standing still we set a threshold
	if (abs(val) > angleThreshold){		
		// To calculate the angular rate (the current speed we are turning at)
		float angularRate = val/gain;
		
		// Integrate the angular rate to get the new difference in angle
		float angle = angularRate*gyrotime;
		
		// Add the change to our current angle which gives us the angle which 
		// we are standing in compared to the original angle
		currentAngle += angle;
		
		// To keep the angle within 0 to 360 degrees we either subtract or add 360 degrees 
		// as soon as we go over 360 degrees or below 0 degrees
		while (currentAngle > 359){
			currentAngle -= 360;
		}
		while (currentAngle < 0){
			currentAngle += 360;
		}
	}
}

void getBias()
{
	
	_delay_ms(1);
	// Make a read straight in the beginning to give a value which will count as 0 degrees
	
	int sum = 0;	
	
	for (int i = 0; i < 5; i++)
	{
		_delay_ms(1);
		sum += adcGyro();
	}	
	
	int average = sum/5;
	
	
	defaultAngle = average;
}

void initTimer(){	
	// Set what frequency the timer will run on, setting the prescalar to 1024
	// will give us a clock which counts to 15625, since we have a 16MHz clock 
	// Set prescalar to 1024
	sbi(TCCR2B, CS22);
	sbi(TCCR2B, CS21);
	sbi(TCCR2B, CS20);
	
	// Enables the timer interrupt
	sbi(TIMSK2, OCIE2A);
	
	// Set the timer mode to be CTC(Clear timer on Compare match)
	// Making the timer to count to the value specified in OCR2A and then reset
	sbi(TCCR2B,WGM12);
	
	// Setting the OCR2A to 50 will give us an interrupt which occurs every 3ms 
	OCR2A = 50;
	
}

void gyroInit()
{
	// Initiate the ADC
	adcInit();	
	// Initatate the timer used for the gyro
	initTimer();
}
