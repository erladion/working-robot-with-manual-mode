/*
 * BusValues.h
 *
 * Created: 12/6/2015 4:08:08 PM
 *  Author: piehe154
 */ 


#ifndef BUSVALUES_H_
#define BUSVALUES_H_

//Declaring all the sensor variables that we receinve from the bus and later use in the various parts of the steering module
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

// Updates the correct variable given the value and given which index it has among the values we receive on the bus
void updateBusValues(int var, int index);

#endif /* BUSVALUES_H_ */
