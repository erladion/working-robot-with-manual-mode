#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <avr/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Display.h"
#include "DebugHelp.h"


//Ports
//Data
#define DB7 PD7
#define DB6 PD6
#define DB5 PD5
#define DB4 PD4

//Read/Write
#define RW	PD3

//Register Select
#define RS	PD2

//Enable
#define EN	PD1

//Alias for Enable bit
#define LCD_EN 0x02

//Alias for RS bit
#define LCD_RS 0x04

volatile bool whiteSpaceSwitch = true;

void lcd_init()
{	
	DDRD |= 0xFF;
	
	//Wait for power
	_delay_ms(1000);
	
	//Function set, 2-line mode, 5x7 Dots
	PORTD = (1<<DB5) | (1<<EN);
	_delay_ms(1);
	PORTD = (1<<DB5);
	_delay_ms(1);
	PORTD = (1<<DB5) | (1<<EN);
	_delay_ms(1);
	PORTD = (1<<DB5);
	_delay_ms(1);
	PORTD = (1<<DB7) | (1<<EN);
	_delay_ms(1);
	PORTD = (1<<DB7);
	_delay_ms(1);
	
	//Display on, cursor off, blink off
	PORTD = (1<<EN);
	_delay_ms(1);
	PORTD = 0x00;
	_delay_ms(1);
	PORTD = (1<<DB7) | (1<<DB6) | (1<<EN);
	_delay_ms(1);
	PORTD = (1<<DB7) | (1<<DB6);
	_delay_ms(1);
	
	//Clear the screen
	lcd_cmd(0x01);
	_delay_ms(100);	
}

void lcd_cmd(unsigned char cmd)
{
	PORTD = (cmd & 0xF0) | LCD_EN;
	_delay_ms(1);
	PORTD = (cmd & 0xF0);
	_delay_ms(1);
	PORTD = ((cmd << 4) & 0xF0) | LCD_EN;
	_delay_ms(1);
	PORTD = ((cmd << 4) & 0xF0);
	_delay_ms(1);
}

void lcd_data(unsigned char data)
{
	PORTD = (data & 0xF0) | LCD_EN | LCD_RS;
	_delay_ms(1);
	PORTD = (data & 0xF0) | LCD_RS;
	_delay_ms(1);
	PORTD = ((data << 4) & 0xF0) | LCD_EN | LCD_RS;
	_delay_ms(1);
	PORTD = ((data << 4) & 0xF0) | LCD_RS;
	_delay_ms(1);
}

void lcd_print(char *string)
{
	unsigned int i;
	for (i = 0; string[i]!=0; i++) {
		lcd_data(string[i]);
	}
}

char* lcd_build_row(char *label1, char *data1, char *label2, char *data2)
{
	static char tmpStr[17];
	strcpy(tmpStr, label1);
	strcat(tmpStr, data1);
	strcat(tmpStr, label2);
	strcat(tmpStr, data2);
	return tmpStr;
}

char* lcd_whitespace_adder(char *str, int max_length)
{
	static char result1[6];
	static char result2[6];
	int length = strlen(str);
	if (whiteSpaceSwitch)
	{
		strcpy(result1, " ");
		while(length < max_length) {
			strcat(result1, " ");
			length++;
		}
		strcat(result1, str);
		whiteSpaceSwitch = false;
		return result1;
	}
	else
	{
		strcpy(result2, " ");
		while(length < max_length) {
			strcat(result2, " ");
			length++;
		}
		strcat(result2, str);
		whiteSpaceSwitch = true;
		return result2;
	}
	
}

void lcd_update(bool manualMode, int gyro, int usf, int usr,int irfl, int irfr, int irrl, int irrr)
{
	//Display structure ("_" is whitespace).
	//0123456789012345
	//MODE_0__GYRO_012
	//USF_012__USR_012
	//IRFL_01__IRFR_01
	//IRFL_01__IRFR_01
	
	char str1[10];
	char str2[10];
	
	if(manualMode){
		strcpy(str1, "M");
	}
	else{
		strcpy(str1, "A");
	}
	itoa(gyro,str2,10);
	
	//Write Mode, Gyro
	lcd_cmd(0x80);	//Set row 1 on the display
	lcd_print(lcd_build_row("MODE ", str1, " GYRO", lcd_whitespace_adder(str2, 4)));
	
	itoa(usf,str1,10);
	itoa(usr,str2,10);
	//Write Ultrasound
	lcd_cmd(0xc0);	//Set row 2 on the display
	lcd_print(lcd_build_row("USF", lcd_whitespace_adder(str1, 3), " REF", lcd_whitespace_adder(str2, 4)));
	
	itoa(irfl,str1,10);
	itoa(irfr,str2,10);
	//Write IRFL, IRFR
	lcd_cmd(0x90);	//Set row 3 the display
	lcd_print(lcd_build_row("IRFL", lcd_whitespace_adder(str1, 2), "  IRFR", lcd_whitespace_adder(str2, 2)));
	
	itoa(irrl,str1,10);
	itoa(irrr,str2,10);
	//Write IRRL, IRRR
	lcd_cmd(0xd0);	//Set row 4 the display
	lcd_print(lcd_build_row("IRRL", lcd_whitespace_adder(str1, 2), "  IRRR", lcd_whitespace_adder(str2, 2)));
}
