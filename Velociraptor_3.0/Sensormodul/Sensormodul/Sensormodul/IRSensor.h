/*
 * IRSensor.h
 *
 * Created: 12/1/2015 9:36:15 AM
 *  Author: filma035
 */ 


#ifndef IRSENSOR_H_
#define IRSENSOR_H_

// IR-front left value
volatile uint8_t IRFL;
// IR-front right value
volatile uint8_t IRFR;
// IR-back left value
volatile uint8_t IRBL;
// IR-back right value
volatile uint8_t IRBR;

// Initiate the A/D converter for the ir
void irInit();
// Loop through the pins/channels to which the ir sensors are connected to
void readAllIr();
// Read the A/D value for the specified channel 
int irRead(uint8_t channel);

#endif /* IRSENSOR_H_ */
