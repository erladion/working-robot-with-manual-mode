/*
 * BusSlave.h
 *
 * Created: 11/30/2015 4:20:57 PM
 * Author: filma035, marlu642
 * Version: 1.0
 */ 

#ifndef BUSSLAVE_H_
#define BUSSLAVE_H_

// Variable for checking if data is currently being sent or not
volatile int sending;
// Variable for storing the sensor data that's going to be sent to the communication module
volatile char* TWIdata;
// Variable for indexing through TWIdata
volatile int TWIcounter;   
// Initialize the bus
void initBuss(char address);

#endif /* BUSSLAVE_H_ */
