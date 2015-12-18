/*
 * BusSlave.h
 *
 * Created: 11/30/2015 4:20:57 PM
 * Author: filma035, marlu642
 * Version: 1.0
 */ 


#ifndef BUSSLAVE_H_
#define BUSSLAVE_H_

volatile int sending; // Variable for checking if data is currently being sent or not
volatile char* TWIdata; // Variable for storing the sensor data that's going to be sent to the communications module
volatile int TWIcounter; // Variable for indexing through TWIdata

void initBuss(char address); // Initialize the bus

#endif /* BUSSLAVE_H_ */
