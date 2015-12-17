/*
 * RotateCrossing.h
 *
 * Created: 12/2/2015 4:52:58 PM
 *  Author: piehe154
 */ 


#ifndef ROTATECROSSING_H_
#define ROTATECROSSING_H_

typedef enum {FRONT, BACK} useful_ultrasound;

void rotating_left(int current_angle);
void rotating_right(int current_angle);
void enter_mid_before_rotating_left(double distance, int current_angle, int distanceFront);
void enter_mid_before_rotating_right(double distance,int current_angle, int distanceFront);

void exit_junction_left(int IRFL, int IRBL);
void exit_junction_right(int IRFR, int IRBR);
void exit_junction_forward_in_left_crossing(int IRFL, int IRBL);
void exit_junction_forward_in_right_crossing(int IRFR, int IRBR);
void turn_around(int current_angle);

int correct_req_current_angle(int requested_gyro_value);
void check_if_junction_and_keep_right(int IRFR, int IRBR, int IRFL, int IRBL, int distanceFront, double distance, int current_angle);
void check_if_junction_and_follow_path(int IRFR, int IRBR, int IRFL, int IRBL, int distanceFront, double distance, int current_angle);

void startTurnAround(int current_angle);

int openForward(int sensorFront);
int in_junction(int a, int c);
int out_of_junction(int ir_front, int ir_back);
int partly_open(int ir_front, int ir_back);

#endif /* ROTATECROSSING_H_ */
