/*
 * Gyro.h
 *
 * Created: 12/1/2015 9:53:57 AM
 *  Author: filma035
 *  Version: 1.0
 */ 

#ifndef GYRO_H_
#define GYRO_H_

// Variable for holding the robots current angle
volatile float currentAngle;
// The A/D converted value which counts as 0 degrees
int defaultAngle;

// Initiate the corresponding settings for the gyro
void gyroInit();
// Initiate the timer which is used for integration
void initTimer();
// Initiate the A/D converter
void adcInit();
// Make the A/D read for the gyro
uint16_t adcGyro();
// Calculates the value which will counts as 0 degrees
void getBias();

#endif /* GYRO_H_ */
