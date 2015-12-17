/*
 * BusValues.c
 *
 * Created: 12/7/2015 3:48:27 PM
 *  Author: johja118
 */ 

#include "BusValues.h"

void updateBusValues(int var, int index) {
	switch(index){
		case 2:
			startbutton = ((var & 0b01000000) >> 6);
			//mode = ((var & 0b00001000) >> 3);
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
	/*startbutton = ((TWIdata[2] & 0b01000000) >> 6);
	mode = ((TWIdata[2] & 0b00100000) >> 5);
	reflex = ((TWIdata[3] << 8) + TWIdata[4]);
	currentAngle = ((TWIdata[5] << 8) +TWIdata[6]);
	distanceFront = ((TWIdata[7] << 8) + TWIdata[8]);
	distanceBack = ((TWIdata[9] << 8) + TWIdata[10]);
	IRFR = TWIdata[11];
	IRFL = TWIdata[12];
	IRBR = TWIdata[13];
	IRBL = TWIdata[14];*/
}