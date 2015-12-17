/*
 * NewLabyrinthMemory.h
 *
 * Created: 2015-12-14 22:56:38
 *  Author: Erladion
 */ 


#ifndef NEWLABYRINTHMEMORY_H_
#define NEWLABYRINTHMEMORY_H_

typedef enum{
	wall,
	path,
	unexplored,
	start,
	object
}nodeType;

typedef enum{
	up,
	down,
	left,
	right,
	none
} direction;

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
volatile bool hardMode;

void initLabyrinthMemory();

// Get opposite direction
direction oppositeDirection(direction dir);
direction getGlobalDirection(direction dir);

void addNode(bool openLeft, bool openRight, bool openFront, bool isObject);
void moveInLabyrinth(bool forward);
void turnInLabyrinth(direction dir);

bool checkUnexploredNodes();
bool isCrossing(int x, int y);
bool shouldIGoThisWay(direction dir);
nodeType getNodeTypeInDir(int x, int y, direction dir);
void findBestPath(nodeType type);
void transformToDirectionList();

int getNewX(int x, int dir);
int getNewY(int y, int dir);

#endif /* NEWLABYRINTHMEMORY_H_ */