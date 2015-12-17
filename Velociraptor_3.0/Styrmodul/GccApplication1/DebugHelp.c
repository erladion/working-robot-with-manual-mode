/*
 * DebugHelp.c
 *
 * Created: 12/3/2015 1:16:59 PM
 *  Author: filma035
 */ 

#include <avr/io.h>
#include "DebugHelp.h"

void intToBitArray(int array[], int arraySize, int num){
	int i;
	
	for (i = 0; i < arraySize; ++i)
	{
		array[i] = num & (1 << i) ? 1 : 0;
	}
}

void displayBinaryNumber(int number, int numberSize)
{	
	int array[numberSize];

	intToBitArray(array,numberSize,number);

	for (int i = numberSize; i >= 0; i--)
	{
		pulse(PORTB,0);
		if (array[i] == 1){
			pulse(PORTB,1);
		}
	}
}
