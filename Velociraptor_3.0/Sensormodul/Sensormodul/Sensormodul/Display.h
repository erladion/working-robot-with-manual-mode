/*
 * Display.h
 *
 * Created: 12/1/2015 9:50:30 AM
 *  Author: filma035
 */ 


#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <stdbool.h>

//Initializes the display.
void lcd_init();
//Sends commands to the display.
void lcd_cmd(unsigned char cmd);
//Sends data to the display.
void lcd_data(unsigned char data);
//Prints a string to the display.
void lcd_print(char *string);
//Concatenates the 4 strings from the input.
char* lcd_build_row(char *label1, char *data1, char *label2, char *data2);
//Adds whitespace in front of the the inputed string until it reaches max_length+1.
char* lcd_whitespace_adder(char *str, int max_length);
//Updates the display with the inputed sensor data.
void lcd_update(bool mode, int gyro, int usf, int usr,int irfl, int irfr, int irrl, int irrr);

#endif /* DISPLAY_H_ */
