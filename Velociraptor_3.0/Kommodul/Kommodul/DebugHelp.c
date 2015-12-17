/*
 * DebugHelp.c
 *
 * Created: 12/3/2015 1:16:59 PM
 *  Author: filma035
 */ 

void intToBitArray(int array[], int arraySize, int num){
	int i;
	
	for (i = 0; i < arraySize; ++i)
	{
		array[i] = num & (1 << i) ? 1 : 0;
	}
}
