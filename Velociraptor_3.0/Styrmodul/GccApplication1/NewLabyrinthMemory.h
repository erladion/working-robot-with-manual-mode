/*
 * NewLabyrinthMemory.h
 *
 * Created: 2015-12-14 22:56:38
 *  Author: Erladion
 */ 


#ifndef NEWLABYRINTHMEMORY_H_
#define NEWLABYRINTHMEMORY_H_

// Different objects for the map
typedef enum{
	wall,
	path,
	unexplored,
	start,
	object
}nodeType;

// Different direction the robot can take
typedef enum{
	up,
	down,
	left,
	right,
	none
} direction;

// Different driving modes
typedef enum{
	lookingForObject,
	exploreWithTurningRight,
	goingToObject,
	exploreUnexploredNodes,
	goingOut
} driving_mode;

volatile driving_mode labyrinthmode;
volatile direction lastDirection;

volatile nodeType labyrinth[19][10];

volatile int currentX;
volatile int currentY;

volatile int currentStepInPath;

volatile int bestPath[50][2];
volatile int bestPathLength;
volatile direction bestDirectionPath[50];

bool justFoundTape;
// Variable for using the labyrinth memory or not
// If true we use the labyrinth memory
// otherwise we just keep on going right
volatile bool hardMode;

void initLabyrinthMemory();

// Get opposite direction
direction oppositeDirection(direction dir);
// Get the global direction using our current direction
direction getGlobalDirection(direction dir);

// Adds a node at the robots current X and Y
void addNode(bool openLeft, bool openRight, bool openFront, bool isObject);
// Makes a step in the labyrinth
void moveInLabyrinth(bool forward);
// Makes a turn in the labyrinth
void turnInLabyrinth(direction dir);
// Check if any nodes in the labyrinth memory are unexplored
bool checkUnexploredNodes();
// Check if a certain location in the memory is any type of crossing
bool isCrossing(int x, int y);
// Checks in the direction list if we should go in the direction we send in
bool shouldIGoThisWay(direction dir);
// Gets the nodetype in a specific direction
nodeType getNodeTypeInDir(int x, int y, direction dir);
// Finds the best path in our current memory
void findBestPath(nodeType type);
// Transform a path containing nodes to a direction list which contains directions in which the robot should drive
void transformToDirectionList();

// Gets new X and Y values depending on in which direction we are going
int getNewX(int x, int dir);
int getNewY(int y, int dir);

#endif /* NEWLABYRINTHMEMORY_H_ */
