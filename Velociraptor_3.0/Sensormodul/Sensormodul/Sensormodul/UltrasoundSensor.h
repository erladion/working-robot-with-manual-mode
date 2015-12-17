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

void timer1_init();
void ext_interrupt_init();
double calculate_distance(volatile int end_value);
void ultrasoundInit();


#endif /* ULTRASOUNDSENSOR_H_ */