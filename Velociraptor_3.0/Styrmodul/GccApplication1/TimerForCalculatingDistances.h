/*
 * TimerForCalculatingDistances.h
 *
 * Created: 12/8/2015 9:38:37 PM
 *  Author: johja118
 */ 


#ifndef TIMERFORCALCULATINGDISTANCES_H_
#define TIMERFORCALCULATINGDISTANCES_H_

#include <stdbool.h>

volatile int goingIn;
volatile double timeTraveled;
volatile double rotatedTime;
volatile int exiting_junction;

// Initiate the timer which we use when we calculate for how long we have been going forward and for how long we have been rotating
void initDistanceTimer();
// Start measuring the time for how long we have been travelling
void startMeasuringDistance();
// Stop measuring the time for how long we have been travelling
void stopMeasuringDistance();
// Start measuring the time for how long we have been rotating
void startMeasuringRotateTime();
// Stop measuring the time for how long we have been rotating
void stopMeasuringRotateTime();

#endif /* TIMERFORCALCULATINGDISTANCES_H_ */
