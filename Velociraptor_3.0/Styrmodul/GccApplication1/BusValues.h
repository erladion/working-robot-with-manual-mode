/*
 * BusValues.h
 *
 * Created: 12/6/2015 4:08:08 PM
 *  Author: piehe154
 */ 


#ifndef BUSVALUES_H_
#define BUSVALUES_H_

//Declaring all the bus variables. So that all files point to the same value in memory.
volatile int startbutton;
volatile int mode;
volatile int reflex;
volatile int currentAngle;
volatile int distanceFront;
volatile int distanceBack;
volatile int IRFR;
volatile int IRFL;
volatile int IRBR;
volatile int IRBL;

void updateBusValues(int var, int index);

#endif /* BUSVALUES_H_ */