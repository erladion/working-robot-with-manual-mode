/*
 * BusSlave.h
 *
 * Created: 11/30/2015 4:20:57 PM
 *  Author: filma035
 */ 


#ifndef BUSSLAVE_H_
#define BUSSLAVE_H_

// Variable for storing the sensor data that's going to be received from the communications module
volatile char* TWIdata;
// Variable for indexing through TWIdata
volatile int TWIcounter;
// Initialize the bus
void initBuss(char address);

#endif /* BUSSLAVE_H_ */
