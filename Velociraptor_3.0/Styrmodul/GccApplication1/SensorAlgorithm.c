/*
 * sensoralgoritm.c
 *
 * Created: 11/25/2015 7:41:15 PM
 *  Author: piehe154
 */ 

#include <avr/io.h>
#include "SensorAlgorithm.h"
#include <math.h>

volatile int IR_threshold = 40;

	/* Definition of position in corridor
	
	
						0					28.5
	----------------------------------------------> x-axis.
	
			Robot
			 
	_________Front_______
	|					|
	|    A	    	B	|
	|					|
	|					|
	|	 C			D	|
	|					|
	_________Rear________
	
		(corridor_side_position)
		If C = B or A = D then the robot is in the middle of the corridor.
		
		(corridor_robot_skewness)
		If A = B or C = D then the robot is standing straight in the corridor.
	*/
	
	
int corridor_robot_skewness(int A, int B, int C, int D) 
{
	////Calculate the robots skewness compared to the corridor.
	////If negative, the front of the robot is pointing towards the left wall.
	////If positive, the front of the robot is pointing towards the right wall.
	int result;
	//// If there is no wall to the left, but there is one to the right, the robot regulates only using the right wall
	//if((A > IR_threshold || C > IR_threshold) && B < IR_threshold && D < IR_threshold){
		//result = D-B;
	//}
	//// If there is no wall to the right, but there is one to the left, the robot regulates only using the left wall
	//else if((B > IR_threshold || D > IR_threshold) && A < IR_threshold && C < IR_threshold){
		//result = A-C;
	//}
	//// If we have walls on both sides we can regulate with both
	//else if (A < IR_threshold && B < IR_threshold && C < IR_threshold && D < IR_threshold){
	//}
	//// If there aren't any walls on either side, we cannot regulate at all :(
	//else{
		//result = 0;
	//}
	//
	if((A + B < 60) && (C + D < 60)){
		int left_len_diff = A-C;
		int right_len_diff = D-B;
			
		result = (left_len_diff + right_len_diff) / 2;		
	}
	else{
		if((A > IR_threshold) && (B > IR_threshold)){
			result = 0;
		}	
		else if(A < B){
			if (C < IR_threshold){
				result = A - C;
			}
			else{
				result = 0;
			}
		}
		else{
			if ( D < IR_threshold){
				result = D - B;
			}
			else{
				result = 0;
			}
		}
	}	
	
	return result;
}

int corridor_side_position(int A, int B, int C, int D)
{
	//Calculate the robots distance from the middle of the corridor.
	//If negative, the robot is to the left of the middle of the corridor.
	//If positive, the robot is to the right of the middle of the corridor.
	int result;
		
	if(A + B < 60 && C+D < 60){
		// If we have walls on both sides we can regulate with both
		int dist_from_mid = (A-D)/2;
		int dist_from_mid_2 = (C-B)/2;
			
		result = (dist_from_mid + dist_from_mid_2) /2;		
	}
	else{
		/*
		// If there is no wall to the left, but there is one to the right, the robot regulates only using the right wall
		if((A > IR_threshold || C > IR_threshold) && B < IR_threshold && D < IR_threshold){
			result = (20-B)/2;
		}
		// If there is no wall to the right, but there is one to the left, the robot regulates only using the left wall
		else if((B > IR_threshold || D > IR_threshold) && A < IR_threshold && C < IR_threshold){
			result = (A-20)/2;
		}
		*/
		if (A+B < 60){
			result = (A-B)/2;
		}
		else if (C+D < 60){
			result = (C-D)/2;
		}
		else if((A > IR_threshold) && (B > IR_threshold)){
			result = 0;
		}
		else if(A < B){
			result = (A-20)/2;
		}
		else{
			result = (20-B)/2;
		}		
	}	
	
	return result;	
}