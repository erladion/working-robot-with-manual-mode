/*
 * DebugHelp.c
 *
 * Created: 12/3/2015 1:16:59 PM
 *  Author: filma035
 */ 

// Converts an integer into a bitarray of the specified size and saves it in the specified array
void intToBitArray(int array[], int arraySize, int num){
	int i;
	
	for (i = 0; i < arraySize; ++i)
	{
		array[i] = num & (1 << i) ? 1 : 0;
	}
}

// Converts a bitarray into an integer
int bitArrayToInt(int array[], int arraySize){
	int i;
	int res = 0;
	for (i = 0; i < arraySize; ++i)
	{
		res += ((array[i] == 1) ? pow(2,arraySize-i-1) : 0);
	}
}
