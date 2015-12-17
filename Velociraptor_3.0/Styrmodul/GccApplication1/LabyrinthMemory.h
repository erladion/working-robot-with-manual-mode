///*
 //* labyrinth.h
 //*
 //* Created: 11/27/2015 3:17:35 PM
 //*  Author: filma035
 //*/ 
//
//
//#ifndef LABYRINTH_H_
//#define LABYRINTH_H_
//
//#include <stdbool.h>
//
//typedef enum{
	//up = 0,
	//down = 1,
	//left = 2,
	//right = 3
//} direction;
//
//typedef enum{
	//lookingForObject,
	//exploreWithTurningRight,
	//goingToObject,
	//exploreUnexploredNodes,
	//goingOut
//} driving_mode;
//
//
//typedef struct node node;
//
//struct node{
	//
	//// An array of the nodes connected to this node, in all four directions. They are 0 if there are no (known) connected nodes
	//node* neighbourNodes[4];
	//
	//// An array of the distances to the connected nodes in all four directions. If there are no such node, the distance is 0. If there is a node somewhere,
	//// but you haven't been there yet, the distance is 1 until we know the distance
	//int neighbourDistances[4];
	//
	//bool visited;
//};
//
//typedef struct{
	//node* thisNode;
	//direction nextDirection;
//} pathnode;
//
//typedef struct{
	//pathnode* thisPath[100];
	//int nodeAmount;
	//int pathDistance;
//} path;
//
//
//volatile path* currentPathToFollow;
//volatile int currentStepInPath;
//
//volatile node* labyrinth[19][10];
//volatile node* lastVisitedNode;
//volatile direction lastDirection;
//volatile int currentX;
//volatile int currentY;
//volatile int distanceToLastNode;
//volatile driving_mode labyrinthmode;
//
//volatile node* objectNode;
//volatile node* startingNode;
//
//direction oppositeDirection(direction dir);
//direction getGlobalDirection(direction dir);
//void moveInLabyrinth(bool forward);
//void turnInLabyrinth(direction dir);
//void initLabyrinth();
//void addNode(bool openLeft, bool openRight, bool openFront, bool isObject);
//node* findUnexploredNode();
//path* findBestPath(node* goalNode);
//
//void testLabyrinth();
//
//#endif /* LABYRINTH_H_ */