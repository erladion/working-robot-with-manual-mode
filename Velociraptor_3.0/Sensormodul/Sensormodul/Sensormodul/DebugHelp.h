/*
 * DebugHelp.h
 *
 * Created: 12/1/2015 4:20:38 PM
 *  Author: filma035
 */ 


#ifndef DEBUGHELP_H_
#define DEBUGHELP_H_

// Set the bit in the specified register
#define sbi(port, bit) (port) |= (1 << (bit))
// Clear the bit in the specified register
#define cbi(port, bit) (port) &= ~(1 << (bit))
// Sends a pulse on the specified pin in the specified port, used for debugging
#define pulse(port, bit) cbi(port,bit); sbi(port, bit); cbi(port,bit);

// Converts an integer into a bitarray of the specified size and saves it in the specified array
void intToBitArray(int array[], int arraySize, int num);
// Converts a bitarray into an integer
int bitArrayToInt(int array[], int arraySize);

#endif /* DEBUGHELP_H_ */
