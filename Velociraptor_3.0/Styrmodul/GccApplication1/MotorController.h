/*
 * MotorController.h
 *
 * Created: 11/30/2015 4:14:28 PM
 *  Author: filma035
 */ 


#ifndef MOTORCONTROLLER_H_
#define MOTORCONTROLLER_H_

#define ENGINETHRESHOLD 50
#define ENGINESTEP 20.5

volatile int defaultSpeed;
volatile int rotateSpeed;

void convertToMotorData();

void drive_forward(int speed);
void drive_backwards(int speed);
void stop();
void rotate_left(int speed);
void rotate_right(int speed);

void drive_general(int speed1, int speed2);

void init_motor_timers();

#endif /* MOTORCONTROLLER_H_ */