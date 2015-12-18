/*
 * MotorController.h
 *
 * Created: 11/30/2015 4:14:28 PM
 *  Author: filma035
 */ 


#ifndef MOTORCONTROLLER_H_
#define MOTORCONTROLLER_H_

// Minimum speed when using manual mode
#define ENGINETHRESHOLD 50
// How much we increase the speed for each level in manual mode (from 0 to 9)
#define ENGINESTEP 20.5

// The speed we normally drive with in autonomous mode
volatile int defaultSpeed;
// The speed we normally rotate with in autonomous mode
volatile int rotateSpeed;

// Converts the data received from bluetooth to control commands for the motors
void convertToMotorData();

// Sends steering commands to the motors with the specified speed
void drive_forward(int speed);
void drive_backwards(int speed);
void stop();
void rotate_left(int speed);
void rotate_right(int speed);

// Makes the robot drive with speed1 for the right motor and speed2 for the left motor. Negative speed 
void drive_general(int speed1, int speed2);

// Inititalize the timers used for the motors
void init_motor_timers();

#endif /* MOTORCONTROLLER_H_ */
