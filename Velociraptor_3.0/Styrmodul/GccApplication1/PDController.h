/*
 * PDController.h
 *
 * Created: 12/4/2015 4:22:40 PM
 *  Author: filma035
 */ 

#ifndef PDCONTROLLER_H_
#define PDCONTROLLER_H_

// How much the robot will react on 
#define KD 2.5
// Scale factor which scales the whole return value
#define SCALEFACTOR 4

// Returns a value for deciding how we are standing in the corridor
int reglering(uint16_t irfl, uint16_t irfr, uint16_t irrl, uint16_t irrr);

#endif /* PDCONTROLLER_H_ */
