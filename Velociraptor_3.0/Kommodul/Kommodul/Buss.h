/*
 * Buss.h
 *
 * Created: 12/1/2015 10:35:16 AM
 *  Author: filma035
 */ 


#ifndef BUSS_H_
#define BUSS_H_

#include <stdbool.h>

volatile char* TWIdata;
volatile char TWIaddress;
volatile int TWIlength;
volatile int TWIcounter;
volatile bool firstRead;

volatile bool manualMode;

volatile char sensorData[12];

volatile bool sending;

void initBuss();
// Sends a specified amount of data to the specificed adress/module
void sendData(char address, char* data, int datalength);
// Tell the device at the specified adress that we want data
void readData(char address);

#endif /* BUSS_H_ */
