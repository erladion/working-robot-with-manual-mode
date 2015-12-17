/*
 * BusSlave.h
 *
 * Created: 11/30/2015 4:20:57 PM
 *  Author: filma035
 */ 


#ifndef BUSSLAVE_H_
#define BUSSLAVE_H_

#define SensorSize 13

volatile char* TWIdata;
volatile int TWIcounter;

void initBuss(char address);

volatile int sensor;

#endif /* BUSSLAVE_H_ */