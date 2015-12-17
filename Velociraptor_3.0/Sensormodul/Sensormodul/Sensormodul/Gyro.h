/*
 * Gyro.h
 *
 * Created: 12/1/2015 9:53:57 AM
 *  Author: filma035
 */ 


#ifndef GYRO_H_
#define GYRO_H_

volatile float currentAngle;
int defaultAngle;

void gyroInit();
void initTimer();
void adcInit();
uint16_t adcGyro();
void getBias();

#endif /* GYRO_H_ */