///*
 //* Labyrintminne.c
 //*
 //* Created: 11/26/2015 1:08:36 PM
 //*  Author: filma035
 //*/ 
//
//#include "LabyrinthMemory.h"
//
///* Description of "local" and "global directions
	//Local direction is the direction at which the robot is going in relation to itself. For example forward is always "up", and turning left is always "left"
	//
	//Global direction is the direction at which the robot is going in relation to the map. For example going "north" is "up", and going "west" is "left".
	//
//For example:
///*
//__________    ^
//|         |   | (global up)
//|   _     |
//|  |_|->  |
//|         |
//|         |
//|_________|
//The robot drives to the right. Its local "up", is the global "right". Now the robot wants to turn left in relation to itself, which is the global direction up.
//
//*/
//
//// Get opposite direction
//direction oppositeDirection(direction dir){
	//if (dir == down) return up;
	//if (dir == up) return down;
	//if (dir == left) return right;
	//if (dir == right) return left;
//}
//
//// Converts a local direction to a global direction. 
//direction getGlobalDirection(direction dir){
	//if (dir == up) return lastDirection;
	//else if (lastDirection = up){
		//return dir;
	//}
	//else if (lastDirection = down){
		//if (dir == down) return up;
		//if (dir == left) return right;
		//if (dir == right) return left;
	//}
	//else if (lastDirection = left){
		//if (dir == down) return right;
		//if (dir == left) return down;
		//if (dir == right) return up;
	//}
	//else if (lastDirection = right){
		//if (dir == down) return left;
		//if (dir == left) return up;
		//if (dir == right) return down;
	//}
//}
//
//// Updates the coordinates when moving forward or backwards
//void moveInLabyrinth(bool forward){
	//direction globalDir = lastDirection;
	//if (!forward) globalDir = oppositeDirection(globalDir);
	//if (globalDir == up) currentY++;
	//if (globalDir == down) currentY--;
	//if (globalDir == left) currentX--;
	//if (globalDir == right) currentX++;
	//distanceToLastNode++;
//}
//
//// Set the new "lastDirection" to the correct global direction. Used when turning.
//void turnInLabyrinth(direction dir){
	//lastDirection = getGlobalDirection(dir);
//}
//
////Create the labyrinth and the starting node
//void initLabyrinth(){
		//node* firstNode;
		//startingNode = firstNode;
		//
		////Since we can go forward, set the distance to 1
		//firstNode->neighbourDistances[up] = 1;
		//
		////Place it in the correct place in the labyrinth
		//currentX = 9;
		//currentY = 0;
		//labyrinth[9][0] = firstNode;		
		//
		//lastVisitedNode = firstNode;
		//lastDirection = up;
		//
		//currentPathToFollow = 0;
		//labyrinthmode = goingToObject;
//}	
//
////Add a node with a distance to the last node, and specify which of the directions from here that are open.
//void addNode(bool openLeft, bool openFront, bool openRight, bool isObject){
	//node* newNode;
	//if (isObject){
		//setObjectNode(newNode);
	//}
	//bool new = true;
	//
	//// If we have already been here, set the newNode to the actual node we already have
	//if (labyrinth[currentX][currentY] != 0){
		//newNode = labyrinth[currentX][currentY];
		//new = false;
		//node* unexplored = findUnexploredNode();
		//if (newNode == startingNode && unexplored != 0){
			//currentPathToFollow = findBestPath(unexplored);
			//currentStepInPath = 0;
		//}
	//}
	//// otherwise, place the newNode at the correct place in the labyrinth
	//else{
		//labyrinth[currentX][currentY] = newNode;
	//}
	////Link the new node and the last visited node together by setting their neighbours to each other, and set the correct distance between them
	//newNode->neighbourNodes[oppositeDirection(lastDirection)] = lastVisitedNode;
	//newNode->neighbourDistances[oppositeDirection(lastDirection)] = distanceToLastNode;
	//lastVisitedNode->neighbourNodes[lastDirection] = newNode;
	//lastVisitedNode->neighbourDistances[lastDirection] = distanceToLastNode;
	//
	//// If it is a new node, set the distance to 1 at the directions were we can go.
	//if (new){
		//for (int dir = 0; dir < 4; dir++)
		//{
			//if (dir != oppositeDirection(lastDirection)){
				//newNode->neighbourNodes[dir] = 0;
			//}
		//}
		//if (openLeft){
			//newNode->neighbourDistances[getGlobalDirection(left)] = 1;
		//}
		//if (openFront){
			//newNode->neighbourDistances[getGlobalDirection(up)] = 1;
		//}
		//if (openRight){
			//newNode->neighbourDistances[getGlobalDirection(right)] = 1;
		//}
	//}	
	//distanceToLastNode = 0;
	//
	//if (labyrinthmode == exploreWithTurningRight && findUnexploredNode() == 0){
		//labyrinthmode = goingToObject;
		//currentPathToFollow = findBestPath(objectNode);
		//currentStepInPath = 0;
	//}
//}
//
//void setObjectNode(node* object){
	//objectNode = object;
//}
//
//// Finds the best path between our current position and a specific node
//path* findBestPath(node* goalNode){
	//path* pathList[100];
	//int pathListLength = 0;
	//
	//for (int x = 0; x < 19; x++)
	//{
		//for (int y = 0; y < 10; y++)
		//{
			//if (labyrinth[x][y] != 0)
			//{
				//labyrinth[x][y]->visited = false;
			//}
		//}
	//}
	//
	//path* completePath = 0;
	//// Saves the current node as our starting node
	//node* firstNode = labyrinth[currentX][currentY];
	//// Loops through the direction we can go to from our current node
	//for (int i = 0; i < 4; i++)
	//{
		//// Checks if we can go this direction
		//if (firstNode->neighbourDistances[i] > 0){
			//// If we can, we make a new path and add the current node and the chosen direction to it
			//path* newPath;
			//pathnode* newNode;
			//newNode->thisNode = firstNode;
			//newNode->nextDirection = i;
			//newPath->thisPath[0] = newNode;
			//newPath->nodeAmount = 1;
			//// Sets the paths distance to the distance to the next node
			//newPath->pathDistance = firstNode->neighbourDistances[i];
			//// Adds the path to our pathList to the next free index
			//pathList[pathListLength] = newPath;
			//pathListLength++;
		//}
	//}
	//
	//for (int i = 0; i < pathListLength; i++)
	//{
		//path* currentPath = pathList[i];
		//
		//pathnode* previousNode = currentPath->thisPath[currentPath->nodeAmount];
		//
		//node* currentNode = previousNode->thisNode->neighbourNodes[previousNode->nextDirection];
		//
		//// If we have reached our goal
		//if (currentNode == goalNode){
			//// If this is the first complete path we have, we save it and keep looking
			//if (completePath = 0){
				//completePath = currentPath;
				//continue;
			//// Otherwise, we take the shortest path of the 2 paths we have and return it
			//}else{
				//if (completePath->pathDistance > currentPath->pathDistance){
					//return completePath;
				//}
				//else{
					//return currentPath;
				//}
			//}
		//}
		//
		//for (int dir = 0; dir < 4; dir++)
		//{
			//// We will not go backwards, so not the opposite direction of the previous one.
			//if (oppositeDirection(previousNode->nextDirection) == dir){
				//continue;
			//}
			//// We check if there is  a node here
			//if (currentNode->neighbourDistances[dir] > 0  && (currentNode->neighbourNodes[i]->visited == false))
			//{
				//// If we can, we make a new path and add the current node and the chosen direction to it
				//path* newPath;
				//pathnode* newNode;
				//currentNode->visited = true;
				//newNode->thisNode = currentNode;
				//newNode->nextDirection = i;
				//// We copy the old path to the new path and add the newest node to the path
				//memcpy(newPath->thisPath,currentPath->thisPath,currentPath->nodeAmount);
				//newPath->thisPath[currentPath->nodeAmount] = newNode;
				//newPath->nodeAmount = currentPath->nodeAmount + 1;
				//// Sets the path's distance to the previous distance + the distance to the next node
				//newPath->pathDistance = currentPath->pathDistance+firstNode->neighbourDistances[i];
				//// Adds the path to our pathList to the next free index
				//pathList[pathListLength] = newPath;
				//pathListLength++;
			//} 
		//}
	//}
//}
//
//node* findUnexploredNode(){
	//for (int x = 0; x < 19; x++)
	//{
		//for (int y = 0; y < 10; y++)
		//{
			//if (labyrinth[x][y] != 0){
				//for (int dir = 0; dir < 4; dir++)
				//{
					//if (labyrinth[x][y]->neighbourDistances[dir] == 1 && labyrinth[x][y]->neighbourNodes[dir] == 0){
						//return labyrinth[x][y];
					//}
				//}
			//}
		//}
	//}
	//return 0;
//}
//
//
//void testLabyrinth(){
	//initLabyrinth();
	//moveInLabyrinth(true);
	//addNode(true,true,false,false);
	//turnInLabyrinth(left);
	//moveInLabyrinth(true);
	//moveInLabyrinth(true);
	//moveInLabyrinth(true);
	//addNode(false,false,false,false);
	//turnInLabyrinth(down);
	//moveInLabyrinth(true);
	//moveInLabyrinth(true);
	//moveInLabyrinth(true);
	//addNode(true,false,true,false);
	//turnInLabyrinth(left);
	//moveInLabyrinth(true);
	//moveInLabyrinth(true);
	//addNode(false,false,false,false);	
//}