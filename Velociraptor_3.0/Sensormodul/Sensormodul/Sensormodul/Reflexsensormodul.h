
#ifndef REFLEXSENSORMODUL_H_
#define REFLEXSENSORMODUL_H_

volatile int reflex_data;

volatile int reflexValue1;
volatile int reflexValue11;

volatile int whiteValue[10];
volatile int blackValue[10];
volatile int threshold[11];

volatile int reflexValues[11];


int adcRead();

void reflex_init();
void reflex_run(int channel_select);
void reflex_run_all();

void calibrateReflexSensors();




#endif /* REFLEXSENSORMODUL_H_ */