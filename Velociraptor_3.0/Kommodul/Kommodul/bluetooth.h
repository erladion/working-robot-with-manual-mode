/*
 * bluetooth.h
 *
 * Created: 11/23/2015 4:40:44 PM
 *  Author: filma035
 */ 


#ifndef BLUETOOTH_H_
#define BLUETOOTH_H_

#include <stdbool.h>

volatile int command;
volatile int speed;
volatile int turnrate;

volatile char bluetoothData[3];

// Send a specified char
void UART_TxChar(unsigned char data);
// Send a string
void UART_TxStr(char *str, int num);
// Initiate the bluetooth
void initBluetooth();
// Read the next char that comes
unsigned char USARTReadChar(void);
// Sends back the data that we recieved, used for debugging
void sendBackCommand();


#endif /* BLUETOOTH_H_ */
