/*
 * RotateCrossing.c
 *
 * Created: 12/2/2015 8:44:37 AM
 *  Author: piehe154
 */ 


#include <avr/io.h>
#include <stdbool.h>
#include <math.h>
#include "RotateCrossing.h"
#include "Mode.h"
#include "MotorController.h"
#include "TimerForCalculatingDistances.h"
#include "NewLabyrinthMemory.h"

volatile int requested_vertical_value = 0;

volatile int errorCount = 0; 

//Length of one square in labyrinth.
static volatile int IR_threshold = 50; 

// The time we will drive forward in a junction before we begin to rotate
static volatile int TIME_INTO_MID_CROSSING = 15;

// The time we rotate when rotating 90 degrees
static volatile int rotateTime = 90;

void rotating_left(int current_angle){	
	// If we are done rotating, exit the junction. Otherwise, keep rotating.
	if(rotatedTime > rotateTime){
		turnInLabyrinth(left);
		current_mode = EXIT_JUNCTION_LEFT;	
	}
	else{
		rotate_left(rotateSpeed);
	}
}

void rotating_right(int current_angle){
	// If we are done rotating, exit the junction. Otherwise, keep rotating.
	if(rotatedTime > rotateTime){
		turnInLabyrinth(right);
		current_mode = EXIT_JUNCTION_RIGHT;
	}
	else{
		rotate_right(rotateSpeed);
	}
}

void enter_mid_before_rotating_right(double distance, int current_angle, int distanceFront)
{
	if((requested_vertical_value < distance) || !openForward(distanceFront)){
		current_mode = ROTATE_RIGHT;
	}
}

void enter_mid_before_rotating_left(double distance, int current_angle, int distanceFront)
{
	if((requested_vertical_value < distance) || !openForward(distanceFront)){
		current_mode = ROTATE_LEFT;
	}
}

void exit_junction_left(int IRFL, int IRBL){
	int wall_left = out_of_junction(IRBL, IRBL);
	if(wall_left){
		current_mode = STRAIGHT;
	}
}

void exit_junction_right(int IRFR, int IRBR){
	int wall_right = out_of_junction(IRFR, IRBR);
	if(wall_right){
		current_mode = STRAIGHT;
	}	
}

void exit_junction_forward_in_left_crossing(int IRFL, int IRBL){
	int wall_left = out_of_junction(IRFL, IRBL);
	if(wall_left){
		current_mode = STRAIGHT;
	}
}

void exit_junction_forward_in_right_crossing(int IRFR, int IRBR){
	int wall_right = out_of_junction(IRFR, IRBR);
	if(wall_right){
		current_mode = STRAIGHT;
	}
}

void turn_around(int current_angle){
	if(rotatedTime > rotateTime*2){
		turnInLabyrinth(down);
		current_mode = STRAIGHT;
	}
	else{
		rotate_right(rotateSpeed);
	}
}

void check_if_junction_and_keep_right(int IRFR, int IRBR, int IRFL, int IRBL, int distanceFront, double distance, int current_angle){
	// Open means that there's a path that way.
	int open_left = in_junction(IRBL, IRBL);
	int open_right = in_junction(IRFR, IRBR);
	// We only tell the robot that it isn't open to the front if it is bad 50 times in a row
	int open_front = 1;
	if (openForward(distanceFront)){
		errorCount = 0;		
	}
	else{
		errorCount++;
		if (errorCount > 50){
			open_front = 0;
		}
	}
	int partly_open_right = partly_open(IRFR, IRBR);
	int partly_open_left = partly_open(IRFL, IRBL);
	
	// Priorities
	// 1. Right turn
	// 2. Go straight
	// 3. Left turn
	// 4. Dead end (turn around)
	
	// THE GENERAL IDEA
	// We want to rotate right whenever we can.
	// The three situations that can occur for us to want to rotate right are:
	//
	//  Situation 1		 Situation 2		 Situation 3
	//  _______			_____________
	//  | X ___			____  X _____		_____|	 |___
	//	|	|				|	|	 		______ X ____
	//	|   |				|	|				 |   |
	//
	//
	//
	//				  PARTLY OPEN RIGHT
	// Partly open right is when the right front ir sensor(B) doesn't see a wall but the back right ir sensor(D) sees a wall.
	// This is a problem when both the left front ir sensor(A) and left back ir sensor(C) doesn't see a wall.
	// If we didn't think of this situation the robot would rotate left.
	// _________________________________________________
	//
	//					_____________
	//			--------|	A	B	|--------
	//					|			|
	//					|			|
	//					|			|		 ___________
	//			--------|___C____D__|--------|
	//___________							 |
	//			|							 |
	//			|							 |
	//			|							 |
	
	// Right rotate, we always rotate to the right if its possible.
	if (open_right || (open_left && partly_open_right)) {
		// The robot needs to find the center of the square before it starts rotating.
		addNode(partly_open_left, open_right, open_front, false);
		requested_vertical_value = distance + TIME_INTO_MID_CROSSING;
		current_mode = ENTER_MID_BEFORE_ROTATING_RIGHT;
	}
	else if(open_front) {
		// Keep driving forward
	}
	// Rotate left if it is closed both forward and to the right
	else if(open_left) {
		addNode(open_left, partly_open_right, open_front, false);
		current_mode = ROTATE_LEFT;
	}
	// dead-end, rotate 180*.
	else {
		addNode(false,false,false, false);
		startTurnAround(current_angle);
	}
}

void check_if_junction_and_follow_path(int IRFR, int IRBR, int IRFL, int IRBL, int distanceFront, double distance, int current_angle){
	// Open means that there's a path that way.
	int open_left = in_junction(IRFL, IRBL);
	int open_right = in_junction(IRFR, IRBR);
	
	if (open_left || open_right)
	{
		// We check if it is open in that direction and if our path tells us to go there. In that case, we go there.
		if(open_right && shouldIGoThisWay(right)){
			
			requested_vertical_value = distance + TIME_INTO_MID_CROSSING;
			current_mode = ENTER_MID_BEFORE_ROTATING_RIGHT;
			currentStepInPath++;
		}
		else if (open_left && shouldIGoThisWay(left)){
			requested_vertical_value = distance+TIME_INTO_MID_CROSSING;
			current_mode = ENTER_MID_BEFORE_ROTATING_LEFT;
			currentStepInPath++;
		}
		else if((distanceFront > 25) && shouldIGoThisWay(up)){
			current_mode = GO_FORWARD_IN_RIGHT_JUNCTION;
			currentStepInPath++;
		}
	}
	else if (shouldIGoThisWay(down)){
		startTurnAround(current_angle);
		currentStepInPath++;
	}
}

void startTurnAround(int current_angle){
	current_mode = TURN_AROUND;
}

int in_junction(int ir_front, int ir_back) 
{
	// We check if both sensors are above the threshold
	return ((ir_front > IR_threshold) && (ir_back > IR_threshold));
}

int openForward(int sensorFront){
	return sensorFront >= 25;
}

int out_of_junction(int ir_front, int ir_back)
{	
	return ((ir_front < IR_threshold) && (ir_back < IR_threshold));
}

int partly_open(int ir_front, int ir_back)
{
	return ((ir_front > IR_threshold) && !(ir_back > IR_threshold));
}
