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

void UART_TxChar(unsigned char data);
void UART_TxStr(char *str, int num);
void initBluetooth();
unsigned char USARTReadChar(void);
void sendBackCommand();


#endif /* BLUETOOTH_H_ */