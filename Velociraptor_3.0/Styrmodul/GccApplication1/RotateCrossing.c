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
//#include "LabyrinthMemory.h"
#include "MotorController.h"
#include "TimerForCalculatingDistances.h"
#include "NewLabyrinthMemory.h"

volatile useful_ultrasound current_useful_ultrasound;
volatile int requested_current_angle; // The gyro value which the robot is rotating to.
volatile int requested_vertical_value = 0; // The value from either the front or back ultrasound sensor which the robot will drive to before rotating.

volatile int angleThreshold = 7;
volatile int errorCount = 0;

volatile int test_variable = 0;
static volatile int IR_threshold = 50; //Length of one square in labyrinth.
static volatile int MIN_LEN_FORWARD = 18.5; //Min dist to front wall.

static volatile int TIME_INTO_MID_CROSSING = 15;

volatile int counter = 0;

volatile bool exiting = false;

static volatile int rotateTime = 90;

int ownAbs(int val){
	if (val > 0) {
		return val;
	}
	else{
		return -1*val;
	}
	
}

// Rotate left until the gyro value has moved to request_current_angle with a margin defined by angleThreshold.
void rotating_left(int current_angle){	
	/*
	if(ownAbs(current_angle - requested_current_angle) <= angleThreshold) {
		turnInLabyrinth(left);
		current_mode = EXIT_JUNCTION_LEFT;
	}
	else{
		rotate_left(rotateSpeed);
	}
	*/
	
	if(rotatedTime > rotateTime){ // Was 100 2015-12-15
		turnInLabyrinth(left);
		current_mode = EXIT_JUNCTION_LEFT;	
	}
	else{
		rotate_left(rotateSpeed);
	}
}

// rotate right until the gyro value has moved to request_current_angle with a margin defined by angleThreshold.
void rotating_right(int current_angle){
	/*if(ownAbs(current_angle - requested_current_angle) <= angleThreshold)
	{
		turnInLabyrinth(right);
		current_mode = EXIT_JUNCTION_RIGHT;
	}
	else{
		rotate_right(rotateSpeed);
	}*/
	
	if(rotatedTime > rotateTime){ // Was 100 2015-12-15
		turnInLabyrinth(right);
		current_mode = EXIT_JUNCTION_RIGHT;
	}
	else{
		rotate_right(rotateSpeed);
	}
}

//Check if the robot is in the middle before entering a corner with a 6cm margin, then change mode and give requested rotating end value.
void enter_mid_before_rotating_right(double distance, int current_angle, int distanceFront)
{
	// Check if we are using the front ultrasound to determine if we are in the mid yet.
	/*if (current_useful_ultrasound == FRONT) {
		if (abs(distanceFront - requested_vertical_value) <= 3) {
			current_mode = ROTATE_RIGHT;
			requested_current_angle = correct_req_current_angle(current_angle + 270);
		}
		// If current_useful_ultrasound is not front, it must be back.
		} else {
		if (abs(distanceBack - requested_vertical_value) <= 3) {
			current_mode = ROTATE_RIGHT;
			requested_current_angle = correct_req_current_angle(current_angle + 270);
		}
	}*/
	if((requested_vertical_value < distance) || !openForward(distanceFront)){
		requested_current_angle = correct_req_current_angle(current_angle + 270);
		current_mode = ROTATE_RIGHT;
	}
}

//Check if the robot is in the middle before entering a corner with a 6cm margin, then change mode and give requested rotating end value.
void enter_mid_before_rotating_left(double distance, int current_angle, int distanceFront)
{
	// Check if we are using the front ultrasound to determine if we are in the mid yet.
	/*if (current_useful_ultrasound == FRONT) {
		if (abs(distanceFront - requested_vertical_value) <= 3) {
			current_mode = ROTATE_RIGHT;
			requested_current_angle = correct_req_current_angle(current_angle + 270);
		}
		// If current_useful_ultrasound is not front, it must be back.
		} else {
		if (abs(distanceBack - requested_vertical_value) <= 3) {
			current_mode = ROTATE_RIGHT;
			requested_current_angle = correct_req_current_angle(current_angle + 270);
		}
	}*/
	if((requested_vertical_value < distance) || !openForward(distanceFront)){
		requested_current_angle = correct_req_current_angle(current_angle + 90);
		current_mode = ROTATE_LEFT;
	}
}

// Check if the robot has left the junction after its left rotation and in that case set current_mode to STRAIGHT
void exit_junction_left(int IRFL, int IRBL){
	int wall_left = out_of_junction(IRBL, IRBL);
	if(wall_left){
		current_mode = STRAIGHT;
	}
}

// Check if the robot has left the junction after its right rotation and in that case set current_mode to STRAIGHT
void exit_junction_right(int IRFR, int IRBR){
	int wall_right = out_of_junction(IRFR, IRBR);
	if(wall_right){
		current_mode = STRAIGHT;
	}	
	//if(exiting){
		//// 150 => 1s
		//if(exiting_junction > 100){
			//exiting_junction = 0;
			//exiting = false;
			//current_mode = STRAIGHT;
		//}
	//}
	//else{
		//exiting_junction = 0;
		//exiting = true;
	//}	
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

// rotate right until the gyro value has moved to request_current_angle with a margin defined by angleThreshold.
void turn_around(int current_angle){
	/*if(abs(current_angle - requested_current_angle) <= angleThreshold)
	{
		turnInLabyrinth(right);
		turnInLabyrinth(right);
		current_mode = STRAIGHT;
	}
	else{
		rotate_right(rotateSpeed);
		//drive_forward(defaultSpeed);
	}*/
	
	if(rotatedTime > rotateTime*2){ // Was 200 2015-12-15
		turnInLabyrinth(down);
		current_mode = STRAIGHT;
	}
	else{
		rotate_right(rotateSpeed);
	}
}

// If the requested gyro value is higher than 360 degrees, reduce it with 360 degrees to get the correct wanted value
int correct_req_current_angle(int angle){
	while(angle > 359){
		angle -= 360;
	}
	while(angle < 0){
		angle += 360;
	}
	return angle;
}

// After gathering the sensor data, find out if the robot is in a junction and set current_mode accordingly.
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
	//int close_to_front_wall = (distanceFront < MIN_LEN_FORWARD); // Check if there is a wall in front of the robot.
	
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
	else if(open_left) {
		addNode(open_left, partly_open_right, open_front, false);
		requested_current_angle = correct_req_current_angle(current_angle + 90);
		current_mode = ROTATE_LEFT;
	}
	// dead-end, rotate 180*.
	else {
		addNode(false,false,false, false);
		startTurnAround(current_angle);
	}
}

/*
void check_if_junction_and_follow_path(int IRFR, int IRBR, int IRFL, int IRBL, int distanceFront, double distance, int current_angle){
		// Open means that there's a path that way.
		int open_left = in_junction(IRFL, IRBL);
		int open_right = in_junction(IRFR, IRBR);
		if (open_right && currentPathToFollow->thisPath[currentStepInPath]->nextDirection == right){
			requested_vertical_value = distance + 18.5;
			current_mode = ENTER_MID_BEFORE_ROTATING_RIGHT;
			currentStepInPath++;
		}
		else if (open_left && currentPathToFollow->thisPath[currentStepInPath]->nextDirection == left){
			requested_vertical_value = distance + 18.5;
			current_mode = ENTER_MID_BEFORE_ROTATING_LEFT;
			currentStepInPath++;
		}
		else if ((open_left || open_right) && currentPathToFollow->thisPath[currentStepInPath]->nextDirection == up){
			currentStepInPath++;
			current_mode = open_left ? GO_FORWARD_IN_LEFT_JUNCTION : GO_FORWARD_IN_RIGHT_JUNCTION;
		}
}
*/

void check_if_junction_and_follow_path(int IRFR, int IRBR, int IRFL, int IRBL, int distanceFront, double distance, int current_angle){
	// Open means that there's a path that way.
	int open_left = in_junction(IRFL, IRBL);
	int open_right = in_junction(IRFR, IRBR);
	
	if (open_left || open_right)
	{
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
	requested_current_angle = correct_req_current_angle(current_angle + 180);
	current_mode = TURN_AROUND;
}

// Check whether or not the robot has found a junction.
int in_junction(int ir_front, int ir_back) 
{
	return ((ir_front > IR_threshold) && (ir_back > IR_threshold));
}


int openForward(int sensorFront){
	//if(sensorFront != 0){
		//return 0;
	//}
	//else{
		//return 1;
	//}
	return sensorFront >= 25; // Was 25 2015-12-15
}

// Check if there is a wall in front of us.
//int close_to_front_wall(int distanceFront) {
	//return (distanceFront < MIN_LEN_FORWARD);
//}

// Check whether or not the robot has left the junction.
int out_of_junction(int ir_front, int ir_back)
{	
	return ((ir_front < IR_threshold) && (ir_back < IR_threshold));
}

int partly_open(int ir_front, int ir_back)
{
	return ((ir_front > IR_threshold) && !(ir_back > IR_threshold));
}