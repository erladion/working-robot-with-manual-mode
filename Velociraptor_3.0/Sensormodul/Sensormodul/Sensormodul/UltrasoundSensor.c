/*
 * Ultraljudsensor.c
 *
 * Created: 11/12/2015 11:11:34 AM
 *  Author: piehe154
 
	This code operates the ultrasonic range finder,	which purpose 
	is to measure the distance in front of and behind the robot.
 */ 

#define F_CPU 16000000UL
#include <avr/io.h> // Header to enable data flow control over pins
#include <avr/delay.h> // Header to enable the delay function (maybe util/delay.h)
#include <avr/interrupt.h>
#include "UltrasoundSensor.h"

volatile int start_value_front; // Variable for number of timer counts when echo input PC6 goes high. Start counting here!
volatile int start_value_back; // Variable for number of timer counts when echo input PC6 goes high. Start counting here!
volatile int end_value_front; // Variable for number of timer counts when echo input PC6 goes low. Stop counting here!
volatile int end_value_back; // Variable for number of timer counts when echo input PA7 goes low. Stop counting here!

volatile int difference_front;
volatile int difference_back; 

volatile double distance;

// initialize timer1
void timer1_init()
{
	TCNT1 = 0; // initialize counter
	
	// -- CALCULATION OF OCR1A VALUE TO GENERATE A PULSE EVERY 100ms --
	// OCR1A = (Clock_Speed / (Prescaler * Output_frequency)) - 1
	//		= (16000000 / (64 * 10)) - 1
	//		= 24999
	OCR1A = 24999; // Set CTC compare value to 24999, which is 100 ms (aka 10 Hz)
	TIMSK1 |= (1 << OCIE1A); // enable compare interrupt
	
	TCCR1B |= (1 << WGM12); // Configure timer1 for CTC mode
	
	// OBS!!! TESTING WITH CS12 instead of CS11 which gives a prescale with 1024
	TCCR1B |= (1 << CS11)|(1 << CS10);  // Prescale with 64, setting the frequency of timer1 to 2MHz
}

// initialize external interrupt on PCINT0 and PCINT2
void ext_interrupt_init() {
	PCMSK2 |= (1 << PCINT22); // Enables external interrupt on PC6 (Front)
	PCMSK0 |= (1 << PCINT7); // Enables external interrupt on PA7 (Rear)
	
	// When the PCIE2 bit is set (one) and the I-bit in the Status Register (SREG) is set (one), pin
	// change interrupt 2 is enabled. Any change on any enabled PCINT23..16 pin will cause an interrupt.
	// When the PCIE0 bit is set (one) and the I-bit in the Status Register (SREG) is set (one), pin
	//change interrupt 0 is enabled. Any change on any enabled PCINT7..0 pin will cause an interrupt.
	PCICR |= (1 << PCIE2) | (1 << PCIE0);	
}

double calculate_distance(volatile int end_value){
	double time = end_value * 0.0004;	// SHOULD BE 0.0004!!! 0.0064 is for testing! 4 is how long a clock time period takes in centiseconds
	double distance = 343 * time/2;		// distance = 343 * time/2, (Speed of sound = 343 m/s in air. Divided by two because the signal bounces back and forth)
	return distance; // Distance is in centimeters
	// return end_value*0.0686 also works for returning centimeters probably (it's a simplified version)
}

ISR (TIMER1_COMPA_vect) {
	//_delay_us(250);
	//PCMSK2 &= ~(1 << PCINT22); // Disables external interrupt on PC6 (Front)
	//PCMSK0 &= ~(1 << PCINT7); // Disables external interrupt on PA7 (Rear)
	
	PORTA |= (1 << DDA6);	// Set PTI to 1
	_delay_us(20);			// Count for 20 micro seconds
	PORTA &= ~(1 << DDA6);	// Set PTI to 0
	//_delay_us(250);
	
	//PCMSK2 |= (1 << PCINT22); // Enables external interrupt on PC6 (Front)
	//PCMSK0 |= (1 << PCINT7); // Enables external interrupt on PA7 (Rear)
}

ISR(PCINT2_vect) //interrupt service routine when PCINT2 changes (PC6)
{
	if (!(PINC & (1 << DDC6))) // Check if echo line is falling, thats when we want to stop counting. 
	{
		end_value_front = TCNT1;	// Save the timer value when echo input (PC6) goes low
		difference_front = end_value_front - start_value_front;
		distanceFront = calculate_distance(difference_front);
	}
	else{
		start_value_front = TCNT1;
	}
}

ISR(PCINT0_vect) //interrupt service routine when PCINT0 changes(PA7)
{	
	if (!(PINA & (1 << DDA7)))	// Check if Echo Line is falling, thats when we want to stop counting. 
	{
		end_value_back = TCNT1;	// Save the timer value when echo input (PA7) goes low
		difference_back = end_value_back - start_value_back;
		distanceBack = calculate_distance(difference_back);
	} else 
	{
		start_value_back = TCNT1;
	}
}

void ultrasoundInit()
{
	DDRA |= (1<<DDA6); // Set PTI (PA6) as output
	DDRA &= ~(1 << 7); // Set PA7 as input
	DDRC &= ~(1 << 6); // Set PC6 as input
	
	ext_interrupt_init();
	timer1_init();
}