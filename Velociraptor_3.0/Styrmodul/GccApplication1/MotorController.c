/*
 * GccApplication1.c
 *
 * Created: 11/10/2015 3:26:51 PM
 *  Author: johja118
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/delay.h>
#include "MotorController.h"
#include "DebugHelp.h"
#include "BusValues.h"

void drive_forward(int speed){
	drive_general(speed,speed);
}
void drive_backwards(int speed){
	drive_general(-speed,-speed);
}
void stop(){
	//Motorer
	TCCR0A =  0x00;
	TCCR2A =  0x00;
	
	//Griparm
	//TIMSK1 = (0<<OCIE1A); //Disable timer1 interrupt
}

void rotate_left(int speed){
	drive_general(speed,-speed); 
}

void rotate_right(int speed){
	drive_general(-speed,speed);
}

void drive_general(int speed1, int speed2){	
	TCCR0A =  _BV(WGM10) | _BV(COM1A1);
	TCCR2A =  _BV(WGM10) | _BV(COM1A1);
	if(speed1>0){ // if speed is positive, drive forwards, otherwise drive backwards
		sbi(PORTA,2);
	}
	else{
		cbi(PORTA,2);
		speed1 *= -1;
	}
	if(speed2>0){
		sbi(PORTA,1);
	}
	else{
		cbi(PORTA,1);
		speed2 *= -1;
	}
	OCR2A = speed1;
	OCR0A = speed2;
}


void init_motor_timers()
{
	defaultSpeed = 110; // Was 100 2015-12-15
	rotateSpeed = 100;
	DDRA = 0x00;
	
	DDRB = 0xFF;
	DDRD = 0xFF;
	
	// enable 8 bit PWM, select inverted PWM
	TCCR0A =  _BV(WGM10) | _BV(COM1A1);
	TCCR2A =  _BV(WGM10) | _BV(COM1A1);
	
	
	TCCR0B = 0b00000010;	// Div8 Prescaler	
	OCR0A   = 100; // init value 100
	
	TCCR2B = 0b00000010;	// Div8 Prescaler
	OCR2A   = 100; // init value 100
	
	// Set timer0 and timer2 counter initial value to 0
	TCNT0=0;
	TCNT2=0;
}

void convertToMotorData(char motorData[]){
	// 48 is the ASCII number for 0
	// 47 is the ASCII number for 1
	mode = ((motorData[0] & 0b00001000) >> 3);
	char command = motorData[1] - 48; // Convert from char to int
	char speed = motorData[2] - 47;
	char turnrate = motorData[3] - 47;
	switch(command){
		// Stop
		case 0:
			stop();
			break;
		// Drive forward
		case 1:
			drive_forward(ENGINETHRESHOLD+speed*ENGINESTEP);
			break;
		// Drive backward
		case 2:
			drive_backwards(ENGINETHRESHOLD+speed*ENGINESTEP);
			break;
		// Rotate left
		case 3:
			rotate_left(ENGINETHRESHOLD+speed*ENGINESTEP);
			break;
		// Rotate right
		case 4:
			rotate_right(ENGINETHRESHOLD+speed*ENGINESTEP);
			break;
		// Turn left
		case 5:
			drive_general(ENGINETHRESHOLD+speed*ENGINESTEP,ENGINETHRESHOLD+speed*ENGINESTEP-turnrate*ENGINESTEP);
			break;
		// Turn right
		case 6:
			drive_general(ENGINETHRESHOLD+speed*ENGINESTEP-turnrate*ENGINESTEP,ENGINETHRESHOLD+speed*ENGINESTEP);		
			break;
		default:
			stop();
			break;
	}
}
	
