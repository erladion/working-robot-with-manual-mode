
#ifndef OBJECTDETECTION_H_
#define OBJECTDETECTION_H_

// checks how many of the 11 sensors that are active, between a startindex and a stopindex (the stopindex are not included in the check)
int activatedSensors(int reflexData, int startIndex, int stopIndex);
// Checks if we can see tape
bool objectFinder(int reflexData);
// Follows the middle tape as well as possible, and goes to grab mode as soon as we have found the second tape
void objectCentering(int reflexData);


#endif /* OBJECTDETECTION_H_ */
