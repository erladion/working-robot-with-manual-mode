/*
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

// Drive forward with PD-regulation
void driveForwardPD(){
	 double change = reglering(IRFL, IRFR, IRBL, IRBR);
	 if(change < 0){			 
	 	// We cap the value at 255 to make sure the motors dont get overflow
		 if (defaultSpeed - change > 255){
			 change = defaultSpeed - 255;
		 }	 
		
		 drive_general(defaultSpeed+change,defaultSpeed);
	 }
	 else{
		 if (change+defaultSpeed > 255){
			 change = 255-defaultSpeed;
		 } 
		 drive_general(defaultSpeed,defaultSpeed-change);
	 }
}

int main(void)
{	
	init_motor_timers();
	initDistanceTimer();
	init_gripping_claw_timer();
	initLabyrinthMemory();
	
	// Set this to false to not use the labyrinth memory and just use right turns
	hardMode = false;
	
	TWIdata = "000";
	initBuss(0b00000010);
	goingIn = 1;
	sei();	//global enable interrupts
	
	stop();
	
	currentStepInPath = 0;
	labyrinthmode = lookingForObject;
	
	justFoundTape = false;
	
	int timeToTravelSquare = 175;
	current_mode = STRAIGHT;
	
	_delay_ms(1000);
	while(1)
    	{
    	    // Sets the current mode
    	    // mode 1 = manual
    	    // mode 0 = autonomous
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
				if (!objectFinder(reflex) && current_mode == STRAIGHT && labyrinthmode != goingOut){
					justFoundTape = true;
					addNode(false,false,false,true);
					current_mode = TAPE;
					moveInLabyrinth(true);
				}
				
				else if(!objectFinder(reflex) && labyrinthmode == goingOut && justFoundTape == false && current_mode == STRAIGHT) {
					_delay_ms(50);
					stop();
					while(1);
				}
				
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
						current_mode = STRAIGHT;
						currentStepInPath = 0;
						break;
				
					case TAPE:
						objectCentering(reflex);
						break;
					case ROTATE_LEFT:
						rotating_left(currentAngle);
						if(goingOut && justFoundTape){
							justFoundTape = false;
						}
						break;
			
					case ROTATE_RIGHT:
						if(goingOut && justFoundTape){
							justFoundTape = false;
						}
						rotating_right(currentAngle);
						break;
				
					case ENTER_MID_BEFORE_ROTATING_RIGHT:
						enter_mid_before_rotating_right(timeTraveled, currentAngle,distanceFront);
						driveForwardPD();
						break;
				
					case ENTER_MID_BEFORE_ROTATING_LEFT:
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
				
				// If we are driving forward we measure the time for how long we have been travelling
				if(current_mode == STRAIGHT || current_mode == ENTER_MID_BEFORE_ROTATING_RIGHT || current_mode == EXIT_JUNCTION_LEFT || current_mode == EXIT_JUNCTION_RIGHT){
					startMeasuringDistance();
					stopMeasuringRotateTime();
					rotatedTime = 0;
					// When we have travelled 1 square we update the labyrinth memory
					if (timeTraveled > timeToTravelSquare){
						moveInLabyrinth(1);
						timeTraveled -= timeToTravelSquare;
						addNode(false,false,true,false);
					}
				}
				// If we are rotationg we measure the time for how long we have been rotating
				else if (current_mode == ROTATE_LEFT || current_mode == ROTATE_RIGHT || current_mode == TURN_AROUND){
					startMeasuringRotateTime();
					stopMeasuringDistance();
					timeTraveled = 0;					
				}
				// Otherwise we reset the values and stop measuring
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

