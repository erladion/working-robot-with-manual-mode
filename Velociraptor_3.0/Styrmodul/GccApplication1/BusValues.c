/*
 * BusValues.c
 *
 * Created: 12/7/2015 3:48:27 PM
 *  Author: johja118
 */ 

#include "BusValues.h"

void updateBusValues(int var, int index) {
	// We use a switch statement to save the value in the correct place
	switch(index){
		case 2:
			startbutton = ((var & 0b01000000) >> 6);
			break;
		case 3:			
			reflex = (var << 8);
			break;
		case 4:
			reflex += var;
			break;
		case 5:
			currentAngle = (var << 8);
			break;
		case 6:
			currentAngle += var;
			break;
		case 7:
			distanceFront = (var << 8);
			break;
		case 8:
			distanceFront += var;
			break;
		case 9:
			distanceBack = (var << 8);
			break;
		case 10:
			distanceBack += var;
			break;
		case 11:
			IRFR = var;
			break;
		case 12:
			IRFL = var;
			break;
		case 13:
			IRBL = var;
			break;
		case 14:
			IRBR = var;
			break;
		default:
			break;
	}
}
