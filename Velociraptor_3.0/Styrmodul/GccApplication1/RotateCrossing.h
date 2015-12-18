/*
 * RotateCrossing.h
 *
 * Created: 12/2/2015 4:52:58 PM
 *  Author: piehe154
 */ 


#ifndef ROTATECROSSING_H_
#define ROTATECROSSING_H_

// Rotate left 90 degrees
void rotating_left(int current_angle);
// rotate right 90 degrees
void rotating_right(int current_angle);
// Drive to the middle of the junction before rotating
void enter_mid_before_rotating_left(double distance, int current_angle, int distanceFront);
void enter_mid_before_rotating_right(double distance,int current_angle, int distanceFront);

// Exit the junction before we go back the "STRAIGHT" mode
void exit_junction_left(int IRFL, int IRBL);
void exit_junction_right(int IRFR, int IRBR);
void exit_junction_forward_in_left_crossing(int IRFL, int IRBL);
void exit_junction_forward_in_right_crossing(int IRFR, int IRBR);

// Rotate 180 degrees
void turn_around(int current_angle);

// Check if we are in a junction and follows the right-rule
void check_if_junction_and_keep_right(int IRFR, int IRBR, int IRFL, int IRBL, int distanceFront, double distance, int current_angle);

// Checks if we are in a junction and follows the path specified in the labyrinth memory
void check_if_junction_and_follow_path(int IRFR, int IRBR, int IRFL, int IRBL, int distanceFront, double distance, int current_angle);

// Starts rotating
void startTurnAround(int current_angle);

// Checks if it is open to the front
int openForward(int sensorFront);

// Checks if we are inside a junction
int in_junction(int a, int c);
// Checks if we have left the junction
int out_of_junction(int ir_front, int ir_back);
// Checks if it is partly open on a side
int partly_open(int ir_front, int ir_back);

#endif /* ROTATECROSSING_H_ */
