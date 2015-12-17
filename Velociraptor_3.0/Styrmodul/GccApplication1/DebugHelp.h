/*
 * DebugHelp.h
 *
 * Created: 12/1/2015 4:20:38 PM
 *  Author: filma035
 */ 


#ifndef DEBUGHELP_H_
#define DEBUGHELP_H_


int bitArray[16];

// Set the bit in the specified register
#define sbi(port, bit) (port) |= (1 << (bit))
// Clear the bit in the specified register
#define cbi(port, bit) (port) &= ~(1 << (bit))

#define pulse(port, bit) cbi(port,bit); sbi(port, bit); cbi(port,bit);

void intToBitArray(int array[], int arraySize, int num);
void displayBinaryNumber(int number, int numberSize);

#endif /* DEBUGHELP_H_ */