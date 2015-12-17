/*
 * GrippingClaw.c
 *
 * Created: 12/5/2015 12:50:55 PM
 *  Author: marlu642
 */ 
#define F_CPU 14750000UL
#include <avr/io.h>
#include <avr/delay.h>
#include "DebugHelp.h"


// The gripping claw works using PWM. PWM stands for Pulse Width Modulation. This means that we can generate a pulse whose width (ie duration) that can be altered.
// Servos are another example. They tend to expect a pulse every 20ms - depending on the width of the pulse they move to a given location.


// Make the gripping claw move towards claw_position.
// Good values are somewhere between 250-400. 
// At 250 the claw is closed shut and at 400 the claw is wide open aka claw position.
void grab_object(int claw_position){
	OCR1A = claw_position;
	
	// EMERGENCY SOLUTION IF ALL ELSE FAILS
	//for (int i=0; i < 6; i++)
	//{
		//sbi(PORTD, 5);
		//_delay_ms(1);
		//cbi(PORTD, 5);
		//_delay_ms(20);
	//}
}

// Initializes the gripping claw
void init_gripping_claw_timer()
{	
	DDRD |= (1<<PD5); // Set PWM pin as output
	
	TCNT1 = 0; // Set the initial value of timer1 to 0
	
	// -- CALCULATION OF ICR1 VALUE TO GENERATE A PULSE EVERY 20ms --
	// ICR1 = (Clock_Speed / (Prescaler * Output_PWM_Frequency)) - 1
	//		= (14745000 / (64 * 50)) - 1
	//		= 4606.8125 =~ 4607
	ICR1 = 4607; // Which creates a pulse every 20ms (equal to 50 Hz)
	
	TCCR1A |= (1<<COM1A1)|(1<<WGM11);	// Set timer1 to non inverted PWM
	TCCR1B |= (1<<WGM13)|(1<<WGM12)|(1<<CS11)|(1<<CS10); // Prescale with 64. Set mode to 14(FAST PWM)
	
	grab_object(350);
	//DDRD |= (1<<PD5);
	//TCNT1 = 0;
	//ICR1 = 4607;
	//
	//TCCR1A = _BV(WGM11) | _BV(COM1A1);
	//TCCR1B = (1<<WGM13)|(1<<WGM12)|(1<<CS11)|(1<<CS10);
}