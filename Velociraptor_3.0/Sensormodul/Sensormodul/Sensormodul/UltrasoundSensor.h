/*
 * UltrasoundSensor.h
 *
 * Created: 12/1/2015 9:47:07 AM
 *  Author: filma035
 */ 


#ifndef ULTRASOUNDSENSOR_H_
#define ULTRASOUNDSENSOR_H_

volatile double distanceFront;
volatile double distanceBack;

// Initialize timer 1
void timer1_init();
//  Enable interrupts for PC6 for the front sensor and PA7 for the rear sensor
void ext_interrupt_init();
// Calculate the distance in centimeters based on the timer value
double calculate_distance(volatile int end_value);
// Initialize ultrasound
void ultrasoundInit();


#endif /* ULTRASOUNDSENSOR_H_ */
