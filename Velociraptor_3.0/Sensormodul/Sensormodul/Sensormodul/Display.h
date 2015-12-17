/*
 * Display.h
 *
 * Created: 12/1/2015 9:50:30 AM
 *  Author: filma035
 */ 


#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <stdbool.h>

void lcd_init();
void lcd_cmd(unsigned char cmd);
void lcd_data(unsigned char data);
void lcd_print(char *string);
char* lcd_build_row(char *label1, char *data1, char *label2, char *data2);
char* lcd_whitespace_adder(char *str, int max_length);
void lcd_update(bool mode, int gyro, int usf, int usr,int irfl, int irfr, int irrl, int irrr);

#endif /* DISPLAY_H_ */