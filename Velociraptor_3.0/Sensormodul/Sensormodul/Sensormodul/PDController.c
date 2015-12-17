/*
 * Reglering.c
 *
 * Created: 11/30/2015 1:20:01 PM
 *  Author: johja118
 */ 

#include <avr/io.h>
#include "PDController.h"
#include "SensorAlgorithm.h"


int reglering(uint16_t irfl, uint16_t irfr, uint16_t irrl, uint16_t irrr){

	int position = corridor_side_position(irfl,irfr,irrl,irrr);
	int skewness = corridor_robot_skewness(irfl,irfr,irrl,irrr);	
	
	return KP*position;// + KD*skewness;
}