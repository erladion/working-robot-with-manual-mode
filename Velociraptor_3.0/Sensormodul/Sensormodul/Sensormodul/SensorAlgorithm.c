/*
 * sensoralgoritm.c
 *
 * Created: 11/25/2015 7:41:15 PM
 *  Author: piehe154
 */ 

#include <avr/io.h>
#include "SensorAlgorithm.h"

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
		//Calculate the robots skewness compared to the corridor.
		//If negative, the front of the robot is pointing towards the left wall.
		//If positive, the front of the robot is pointing towards the right wall.
		int left_len_diff = A-C;
		
		int right_len_diff = D-B;
		
		int avg_side_diff = (left_len_diff + right_len_diff) / 2;
		
		return avg_side_diff;
	}
	
	int corridor_side_position(int A, int B, int C, int D)
	{
		//Calculate the robots distance from the middle of the corridor.
		//If negative, the robot is to the left of the middle of the corridor.
		//If positive, the robot is to the right of the middle of the corridor.
		int dist_from_mid = (A-D)/2;
		
		int dist_from_mid_2 = ((C-B)/2);
		
		//Might be a more accurate value??
		dist_from_mid = (dist_from_mid + dist_from_mid_2) /2;
		
		return dist_from_mid;
	}