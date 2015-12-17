/*
 * IRSensor.h
 *
 * Created: 12/1/2015 9:36:15 AM
 *  Author: filma035
 */ 


#ifndef IRSENSOR_H_
#define IRSENSOR_H_

volatile uint8_t IRFL;
volatile uint8_t IRFR;
volatile uint8_t IRBL;
volatile uint8_t IRBR;

void irInit();
void readAllIr();
int irRead(uint8_t channel);

#endif /* IRSENSOR_H_ */