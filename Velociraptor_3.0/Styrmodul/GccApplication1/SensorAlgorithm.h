/*
 * SensorAlgorithm.h
 *
 * Created: 12/4/2015 4:40:50 PM
 *  Author: filma035
 */ 

#ifndef SENSORALGORITHM_H_
#define SENSORALGORITHM_H_

// Gives a value of how skewed the robot is in relation to the walls
int corridor_robot_skewness(int A, int B, int C, int D);
// Gives a value of how far away from the middle the robot is
int corridor_side_position(int A, int B, int C, int D);

#endif /* SENSORALGORITHM_H_ */
