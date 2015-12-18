/*
 * NewLabyrinthMemory.c
 *
 * Created: 2015-12-14 22:43:40
 *  Author: Erladion
 */ 
#define F_CPU 14745000UL
#include <stdbool.h>
#include <avr/delay.h>
#include "NewLabyrinthMemory.h"
#include "GrippingClaw.h"
#include <avr/interrupt.h>

//
//
// This does not quite work, so hardMode is turned off, see steeringmodule.c and NewLabyrinthMemory.H
//
//
//

void initLabyrinthMemory(){
	// Sets all the objects in the labyrinth as walls
	// The labyrinth memory is 19x10 in size so that we dont have to move the nodes around
	for (int x = 0; x < 19; x++)
	{
		for (int y = 0; y < 10; y++)
		{
			labyrinth[x][y] = wall;
		}
	}

	// Sets the starting x and y
	currentX = 9;
	currentY = 0;
	
	// Sets the direction in which we are going
	lastDirection = up;
	
	// Sets a startnode at (9,2) which is our starting location
	labyrinth[9][0] = start;
}

// Get opposite direction
direction oppositeDirection(direction dir){
	if (dir == down) return up;
	if (dir == up) return down;
	if (dir == left) return right;
	if (dir == right) return left;
	return none;
}

// Converts a local direction to a global direction.
direction getGlobalDirection(direction dir){
	if (dir == up) return lastDirection;
	else if (lastDirection == up){
		return dir;
	}
	else if (lastDirection == down){
		if (dir == down) return up;
		if (dir == left) return right;
		if (dir == right) return left;
	}
	else if (lastDirection == left){
		if (dir == down) return right;
		if (dir == left) return down;
		if (dir == right) return up;
	}
	else if (lastDirection == right){
		if (dir == down) return left;
		if (dir == left) return up;
		if (dir == right) return down;
	}
	else{
		return none;
	}
}

// Checks in each direction from the current position to see which kind of nodeType is in that direction
void addNode(bool openLeft, bool openRight, bool openFront, bool isObject){
	if (lastDirection == up){
		labyrinth[currentX][currentY+1] = (openFront ? (labyrinth[currentX][currentY+1] == path ? path : unexplored) : wall);
		labyrinth[currentX-1][currentY] = (openLeft ? (labyrinth[currentX-1][currentY] == path ? path : unexplored) : wall);
		labyrinth[currentX+1][currentY] = (openRight ? (labyrinth[currentX+1][currentY] == path ? path : unexplored) : wall);
	}
	else if (lastDirection == left){
		labyrinth[currentX-1][currentY] = (openFront ? (labyrinth[currentX-1][currentY] == path ? path : unexplored) : wall);
		labyrinth[currentX][currentY-1] = (openLeft ? (labyrinth[currentX][currentY-1] == path ? path : unexplored) : wall);
		labyrinth[currentX][currentY+1] = (openRight ? (labyrinth[currentX][currentY+1] == path ? path : unexplored) : wall);
	}
	else if (lastDirection == down){
		labyrinth[currentX][currentY-1] = (openFront ? (labyrinth[currentX][currentY-1] == path ? path : unexplored) : wall);
		labyrinth[currentX+1][currentY] = (openLeft ? (labyrinth[currentX+1][currentY] == path ? path : unexplored) : wall);
		labyrinth[currentX-1][currentY] = (openRight ? (labyrinth[currentX-1][currentY] == path ? path : unexplored) : wall);
	}
	else if (lastDirection == right){
		labyrinth[currentX+1][currentY] = (openFront ? (labyrinth[currentX+1][currentY] == path ? path : unexplored) : wall);
		labyrinth[currentX][currentY+1] = (openLeft ? (labyrinth[currentX][currentY+1] == path ? path : unexplored) : wall);
		labyrinth[currentX][currentY-1] = (openRight ? (labyrinth[currentX][currentY-1] == path ? path : unexplored) : wall);
	}
	
	if(isObject){
		labyrinth[currentX][currentY] = object;
	}
	else{
		labyrinth[currentX][currentY] = path;
	}
	if (labyrinthmode == exploreWithTurningRight && !checkUnexploredNodes()){
		findBestPath(object);
		currentStepInPath = 0;
	}
}

// Updates the coordinates when moving forward or backwards
void moveInLabyrinth(bool forward){
	direction globalDir = lastDirection;
	if (!forward) globalDir = oppositeDirection(globalDir);
	if (globalDir == up) currentY++;
	if (globalDir == down) currentY--;
	if (globalDir == left) currentX--;
	if (globalDir == right) currentX++;
}

// Set the new "lastDirection" to the correct global direction. Used when turning.
void turnInLabyrinth(direction dir){
	lastDirection = getGlobalDirection(dir);
}

// Gets the nodeType in the specified direction at a specified X and Y
nodeType getNodeTypeInDir(int x, int y, direction dir){
	if (dir == up)
	{
		if (y+1 > 9 || x < 0 || x > 18){
			return wall;
		}
		else{
			return labyrinth[x][y+1];
		}
	}
	else if(dir == right){
		
		if (x+1 > 18 || y < 0 || y > 8){
			return wall;
		}
		else{
			return labyrinth[x+1][y];
		}
	}
	else if(dir == left){
		if (x-1 < 0 || y < 0 || y > 8){
			return wall;
		}
		else{
			return labyrinth[x-1][y];
		}			
	}
	else if (dir == down)
	{
		if (y-1 < 0 || x < 0 || x > 18){
			return wall;
		}
		else{
			return labyrinth[x][y-1];
		}
	}
}

// Finds the best path to a specific nodeType from the current position
void findBestPath(nodeType type){
	int paths [100][50][2];
	int pathLengths[100] = {0};
	int arrayLength = 0;
	currentX = 9;
	currentY = 2;
	
	for (int dir = 0; dir < 4; dir++)
	{
		if((getNodeTypeInDir(currentX, currentY, dir) != wall && (getNodeTypeInDir(currentX,currentY,dir) != unexplored)){
			pathLengths[arrayLength] = 1;
			paths[arrayLength][0][0] = getNewX(currentX, dir);
			paths[arrayLength][0][1] = getNewY(currentY, dir);
			arrayLength++;
		}
	}
	
	for (int p = 0; p < arrayLength; p++)
	{
		if(labyrinth[paths[p][pathLengths[p]-1][0]][paths[p][pathLengths[p]-1][1]] == type){
			for (int i = 0; i < pathLengths[p]; i++)
			{
				bestPath[i][0] = paths[p][i][0];
				bestPath[i][1] = paths[p][i][1];
			}
			
			bestPathLength = pathLengths[p];
			transformToDirectionList();
			return;
		}  
		for (int dir = 0; dir < 4; dir++)
		{
			if(getNodeTypeInDir(paths[p][pathLengths[p]-1][0],paths[p][pathLengths[p]-1][1],dir) != wall && getNodeTypeInDir(paths[p][pathLengths[p]-1][0],paths[p][pathLengths[p]-1][1],dir) != unexplored){
				if (pathLengths[p] > 2){
					if (getNewX(paths[p][pathLengths[p]-1][0],dir) == paths[p][pathLengths[p]-3][0] && 
						getNewY(paths[p][pathLengths[p]-1][1],dir) == paths[p][pathLengths[p]-3][1]){
						continue;
					}
				}
							
				for (int i = 0; i < pathLengths[p]; i++)
				{
					paths[arrayLength][i][0] = paths[p][i][0];
					paths[arrayLength][i][1] = paths[p][i][1];
				}
					
								
				paths[arrayLength][pathLengths[p]][0] = getNewX(paths[p][pathLengths[p]-1][0],dir);
				paths[arrayLength][pathLengths[p]][1] = getNewY(paths[p][pathLengths[p]-1][1], dir);
				pathLengths[arrayLength] = pathLengths[p] + 1;
				arrayLength++;
			}
		}
			
	}
}

void transformToDirectionList(){
	int dirLength = 0;
	for (int i = 0; i < bestPathLength-1; i++)
	{
		if (bestPath[i][0] == bestPath[i+1][0] && bestPath[i][1] == bestPath[i+1][1] - 1){
			if (dirLength == 0){
			}
			else if (bestDirectionPath[dirLength-1] != up || isCrossing(bestPath[i][0],bestPath[i][1])){
				bestDirectionPath[dirLength] = up;
				dirLength++;
			}
		}
		else if (bestPath[i][0] == bestPath[i+1][0] && bestPath[i][1] == bestPath[i+1][1] + 1) {
			if (dirLength == 0){
				bestDirectionPath[dirLength] = down;
				dirLength++;		
			}
			if (bestDirectionPath[dirLength-1] != down || isCrossing(bestPath[i][0],bestPath[i][1])){
				bestDirectionPath[dirLength] = down;
				dirLength++;
			}
		
		}
		else if (bestPath[i][0] == bestPath[i+1][0] -1 && bestPath[i][1] == bestPath[i+1][1]){
			if (dirLength == 0){
				bestDirectionPath[dirLength] = right;
				dirLength++;
			}
			if (bestDirectionPath[dirLength-1] != right || isCrossing(bestPath[i][0],bestPath[i][1])){
				bestDirectionPath[dirLength] = right;
				dirLength++;
			}
		
		}
		else if (bestPath[i][0] == bestPath[i+1][0] +1 && bestPath[i][1] == bestPath[i+1][1]){
			if (dirLength == 0){
				bestDirectionPath[dirLength] = left;
				dirLength++;				
			}
			if (bestDirectionPath[dirLength-1] != left || isCrossing(bestPath[i][0],bestPath[i][1])){
				bestDirectionPath[dirLength] = left;
				dirLength++;
			}
		}
	}
}

bool isCrossing(int x, int y){
	int amount = 0;
	for (int i = -1; i < 2; i++)
	{
		for (int j = -1; j < 2; j++)
		{
			if (x+i > 18 || x+i < 0) continue;
			if (y+j > 9 || y+j < 0) continue;
			if (labyrinth[x+i][y+j] != wall){
				amount++;
			}
		}		
	}
	return amount > 2;
}

int getNewX(int x, int dir){
	if(dir == left){
		return x-1;
	}
	else if(dir == right){
		return x+1;
	}
	else{
		return x;
	}
}

int getNewY(int y, int dir){
	if(dir == down){
		return y-1;
	}
	else if(dir == up){
		return y+1;
	}
	else{
		return y;
	}
}

bool shouldIGoThisWay(direction dir){
	dir = getGlobalDirection(dir);
	return bestDirectionPath[currentStepInPath] == dir;
}

bool checkUnexploredNodes(){
	for (int x = 0; x < 19; x++)
	{
		for (int y = 0; y < 10; y++)
		{
			if (labyrinth[x][y] == unexplored){
				return true;
			}
		}
	}
	return false;
}
