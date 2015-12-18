
#ifndef REFLEXSENSORMODUL_H_
#define REFLEXSENSORMODUL_H_

volatile int reflex_data;

volatile int reflexValue1;
volatile int reflexValue11;

// Array for holding individual thresholds for the sensors
volatile int threshold[11];

// Array which contains the current A/D value from specific sensors
volatile int reflexValues[11];

// Makes an A/D coversion and returns the A/D value 
int adcRead();

// Initiates the reflexsensors
void reflex_init();
// Gets the value for a specific sensor
void reflex_run(int channel_select);
// Gets the values for all the sensors
void reflex_run_all();

// Calibrates the reflexsensors(current implementation does this by adding the value from sensor 1 and 11 and takes the average)
void calibrateReflexSensors();

#endif /* REFLEXSENSORMODUL_H_ */
