/*
 * Mode.h
 *
 * Created: 12/5/2015 5:39:02 PM
 *  Author: piehe154
 */

#ifndef MODE_H_
#define MODE_H_

// Defines each of the modes that the robot can be in
typedef enum {TAPE, ROTATE_LEFT, ROTATE_RIGHT, EXIT_JUNCTION_RIGHT, EXIT_JUNCTION_LEFT, STRAIGHT, \
	 ENTER_MID_BEFORE_ROTATING_RIGHT,ENTER_MID_BEFORE_ROTATING_LEFT, TURN_AROUND, GRAB, GO_FORWARD_IN_LEFT_JUNCTION,GO_FORWARD_IN_RIGHT_JUNCTION} drive_mode;

// Variable containing the current mode which the robot is in
volatile drive_mode current_mode;

#endif /* MODE_H_ */
