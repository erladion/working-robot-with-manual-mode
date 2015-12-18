/*
 * Buss.h
 *
 * Created: 12/1/2015 10:35:16 AM
 *  Author: filma035
 */ 


#ifndef BUSS_H_
#define BUSS_H_

#include <stdbool.h>

// Variable for storing the sensor data that's going to be sent to the steering module
volatile char* TWIdata;
// Variable that's used for saving the currently addressed slave module's address
volatile char TWIaddress;
// Variable for storing the number of bits that's being sent or received
volatile int TWIlength;
// Variable for indexing through TWIdata
volatile int TWIcounter;
// Variable for checking if the robot is in manual mode or not
volatile bool manualMode;
// Variable for storing the data received from the sensors
volatile char sensorData[12];
// Variable for checking if data is currently being sent or not
volatile bool sending;
// Initiates the bus
void initBuss();
// Sends a specified amount of data to the specificed adress/module
void sendData(char address, char* data, int datalength);
// Tell the device at the specified adress that we want data
void readData(char address);

#endif /* BUSS_H_ */
