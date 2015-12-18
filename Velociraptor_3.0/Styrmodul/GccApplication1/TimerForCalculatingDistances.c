/*
 * TimerForCalculatingDistances.c
 *
 * Created: 12/8/2015 9:37:53 PM
 *  Author: johja118
 */ 
#include "TimerForCalculatingDistances.h"
#include "NewLabyrinthMemory.h"
#include <avr/interrupt.h>

bool measure = false;
bool rotating = false;

// This happens about 100 times per second
ISR(TIMER3_COMPA_vect){
	if (measure)
	{
		if(labyrinthmode != goingOut){
			timeTraveled += 1;
		}
		// This is for when the object has been taken and the robot is on its way out of the labyrinth
		else{
			timeTraveled += 0.5;
		}
	}
	// Adds time to for how long we have been rotated depending if we are rotating or not
	if(rotating){
		rotatedTime += 1;
	}
	else{
		rotatedTime += 0;	
	}

	exiting_junction++; // Variable that's needed for keeping track of how long we've been exiting a junction	
}

// Initiate the timer
void initDistanceTimer(){
	TCCR3B |= (1 << CS32) | (1 << WGM32);
	// OCR3A value is calculated by (F_CPU / Prescalar) / 100 to get a timer which counts 1 timer per 10ms
	OCR3AH = (573 >> 8);
	OCR3AL = 573;
	TIMSK3 = (1 << 1);
	
	timeTraveled = 0;
	rotatedTime = 0;
}

void startMeasuringDistance(){
	measure = true;
}

void stopMeasuringDistance(){
	measure = false;
}

void startMeasuringRotateTime(){
	rotating = true;	
}

void stopMeasuringRotateTime(){
	rotating = false;	
}
