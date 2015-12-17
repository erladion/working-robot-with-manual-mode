﻿/*
 * SteeringModule.c
 *
 * Created: 11/30/2015 4:13:53 PM
 *  Author: filma035
 */ 
#define F_CPU 14750000UL
#include <avr/interrupt.h>
#include <stdbool.h>
#include "MotorController.h"
#include "GrippingClaw.h"
#include "BusSlave.h"
#include "NewLabyrinthMemory.h"
#include "RotateCrossing.h"
#include "Mode.h"
#include "PDController.h"
#include "DebugHelp.h"
#include "TimerForCalculatingDistances.h"
#include "BusValues.h"
#include "ObjectDetection.h"
#include <avr/delay.h>

// There are 10 different modes that the robot can be in.
// GRAB: when the robot is grabbing the object.
// TAPE: when the robot is following the tape that marks the object.
// ROTATE_LEFT: when the robot is rotating to the left.
// ROTATE_RIGHT: when the robot is rotating to the right.
// EXIT_JUNCTION_RIGHT: when the robot is exiting the junction after a right rotation has been completed.
// EXIT_JUNCTION_LEFT: when the robot is exiting the junction after a left rotation has been completed.
// TURN_AROUND: when the robot is in a dead-end and is turning around.
// ENTER_MID_BEFORE_ROTATING_LEFT: when the robot has found a junction and has to go the middle of the square before it starts rotating.
// ENTER_MID_BEFORE_ROTATING_RIGHT: when the robot has found a junction and has to go the middle of the square before it starts rotating.
// STRAIGHT: when the robot is going straight.

// BusValues defined here, only this file can change these values.
// These values are defined as extern in BusValues.h so all the files that will use these values will use the same value.
/*int startbutton;
int mode;
int reflex;
int currentAngle;
int distanceFront;
int distanceBack;
int IRFR;
int IRFL;
int IRBR;
int IRBL;*/


// Drive forward with PD-regulation
void driveForwardPD(){
	 double change = reglering(IRFL, IRFR, IRBL, IRBR);
	 if(change < 0){			 
		 if (defaultSpeed - change > 255){
			 change = defaultSpeed - 255;
		 }	 
		
		 drive_general(defaultSpeed+change,defaultSpeed); //drive_general(defaultSpeed,defaultSpeed-change);
	 }
	 else{
		 if (change+defaultSpeed > 255){
			 change = 255-defaultSpeed;
		 } 
		 drive_general(defaultSpeed,defaultSpeed-change); //drive_general(defaultSpeed+change,defaultSpeed);
	 }
}

int main(void)
{	
	init_motor_timers();
	initDistanceTimer();
	init_gripping_claw_timer();
	initLabyrinthMemory();
	
	hardMode = false;
	
	TWIdata = "000";
	initBuss(0b00000010);
	goingIn = 1;
	sei();	//global enable interrupts
	
	stop();
	//
	//labyrinthmode = goingOut;
	//bestPath[0][0] = 9;
	//bestPath[0][1] = 0;
	//bestPath[1][0] = 9;
	//bestPath[1][1] = 1;
	//bestPath[2][0] = 10;
	//bestPath[2][1] = 1;
	//bestPath[3][0] = 10;
	//bestPath[3][1] = 2;
	//bestPath[4][0] = 10;
	//bestPath[4][1] = 3;
	//bestPath[5][0] = 9;
	//bestPath[5][1] = 3;
	//bestPathLength = 6;
	//transformToDirectionList();
	//bestDirectionPath[0] = right;
	//bestDirectionPath[1] = up;
	//bestDirectionPath[2] = left;
	currentStepInPath = 0;
	labyrinthmode = lookingForObject;
	// Good values for grab_object is somewhere between 250-400
	//grab_object(250);
	//_delay_ms(1000);
	//grab_object(350);
	//while(1);
	
	justFoundTape = false;
	
	int timeToTravelSquare = 175;
	current_mode = STRAIGHT;
	
	_delay_ms(1000);
	while(1)
    {
	    if (bit_is_set(PINB, 0)){
		    mode = 1;
	    }
	    else{
		    mode = 0;
	    }
		
	    if (mode == 1){
		    convertToMotorData(TWIdata);
	    }
	    else {
			if(true){
			//drive_forward(defaultSpeed);
				if (!objectFinder(reflex) && current_mode == STRAIGHT && labyrinthmode != goingOut){
					justFoundTape = true;
					addNode(false,false,false,true);
					// If we have explored the whole labyrinth, take the object. Otherwise, keep exploring.
					//if (!checkUnexploredNodes()){
						current_mode = TAPE;
						moveInLabyrinth(true);
					//}
					//else{
						//startTurnAround(currentAngle);
						//labyrinthmode = exploreWithTurningRight;
					//}
				}
				/*
				else if(!objectFinder(reflex) && labyrinthmode == goingOut && justFoundTape == false && current_mode == STRAIGHT) {
					_delay_ms(50);
					stop();
					while(1);
				}
				*/
				
				switch(current_mode)
				{			
					case GRAB:
						stop();
						grab_object(200);
						_delay_ms(200);
						labyrinthmode = goingOut;
						if(hardMode){
							findBestPath(start);
						}	
						//bestDirectionPath[0] = down;
						//bestDirectionPath[1] = down;
						//bestDirectionPath[2] = left;
						current_mode = STRAIGHT;
						currentStepInPath = 0;
						break;
				
					case TAPE:
						objectCentering(reflex);
						//stop();
						break;
					case ROTATE_LEFT:
						//grab_object(200);
						rotating_left(currentAngle);
						if(goingOut && justFoundTape){
							justFoundTape = false;
						}
						break;
			
					case ROTATE_RIGHT:
						//grab_object(200);
						if(goingOut && justFoundTape){
							justFoundTape = false;
						}
						rotating_right(currentAngle);
						break;
				
					case ENTER_MID_BEFORE_ROTATING_RIGHT:
						//grab_object(300);
						enter_mid_before_rotating_right(timeTraveled, currentAngle,distanceFront);
						driveForwardPD();
						break;
				
					case ENTER_MID_BEFORE_ROTATING_LEFT:
						//grab_object(300);
						enter_mid_before_rotating_left(timeTraveled, currentAngle, distanceFront);
						driveForwardPD();
						break;
				
					case EXIT_JUNCTION_LEFT:
						exit_junction_left(IRFL, IRBL);
						driveForwardPD();
						break;
				
					case EXIT_JUNCTION_RIGHT:
						exit_junction_right(IRFR, IRBR);
						driveForwardPD();
						break;	
				
					case TURN_AROUND:
						//stop();
						turn_around(currentAngle);
						break;
				
					case STRAIGHT:
						if (labyrinthmode == goingOut && hardMode){
							check_if_junction_and_follow_path(IRFR, IRBR, IRFL, IRBL, distanceFront, timeTraveled, currentAngle);
						}
						else{
							check_if_junction_and_keep_right(IRFR, IRBR, IRFL, IRBL, distanceFront, timeTraveled, currentAngle);
						}
						driveForwardPD();
						//if(distanceFront != 0){
							//driveForwardPD();
						//}
						//else{
							//stop;
						//}
						break;
				
					case GO_FORWARD_IN_LEFT_JUNCTION:
						exit_junction_forward_in_left_crossing(IRFR, IRBR);
						driveForwardPD();
						break;
			
					case GO_FORWARD_IN_RIGHT_JUNCTION:
						exit_junction_forward_in_right_crossing(IRFR, IRBR);
						driveForwardPD();
						break;
				}
			
				if(current_mode == STRAIGHT || current_mode == ENTER_MID_BEFORE_ROTATING_RIGHT || current_mode == EXIT_JUNCTION_LEFT || current_mode == EXIT_JUNCTION_RIGHT){
					startMeasuringDistance();
					stopMeasuringRotateTime();
					rotatedTime = 0;
					if (timeTraveled > timeToTravelSquare){
						moveInLabyrinth(1);
						timeTraveled -= timeToTravelSquare;
						addNode(false,false,true,false);
					}
				}
				else if (current_mode == ROTATE_LEFT || current_mode == ROTATE_RIGHT || current_mode == TURN_AROUND){
					startMeasuringRotateTime();
					stopMeasuringDistance();
					timeTraveled = 0;					
				}	
				else{
					stopMeasuringDistance();
					timeTraveled = 0;
					stopMeasuringRotateTime();
					rotatedTime = 0;
					
				}
			}
			else
			{
				stop();
			}
		}
	}
}

