
//OBS, sensorerna i modulen ska multiplexas.
//Kontinuerlig drivning av sensorerna gör att dom överhettas och går sönder.
//Dessutom ger en sensor sämre dynamik om närliggande sensor är tänd vid avläsning.

// PB0 = Input
// PB1 = Channel LSB
// PB4 = Channel MSB
// PB5 = Enable

#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <avr/delay.h>
#include "DebugHelp.h"
#include "Reflexsensormodul.h"

void reflex_init()
{
	//PORTB set to output
	DDRB = 0xff;
	//PB0 set as input
	DDRB &= ~(1<<DDB0);
	reflex_data = 0;
	reflexValue1 = 0;
	reflexValue11 = 0;
	threshold[0] = 1024;
	threshold[1] = 780;
	threshold[2] = 580;
	threshold[3] = 710;
	threshold[4] = 750;
	threshold[5] = 620;
	threshold[6] = 670;
	threshold[7] = 650;
	threshold[8] = 660;
	threshold[9] = 620;
	threshold[10] = 1024;
}

int adcRead(){	
	cbi(ADMUX, MUX3);
	sbi(ADMUX, MUX2);
	cbi(ADMUX, MUX1);
	sbi(ADMUX, MUX0);	
	
	// For the ADC to give reliable output we have to make an extra read every time we change channel.
	//(We are also using IR-sensors which need the ADC so we have to do this extra read every time we want a value from the gyro)
	// This read is useless, see AVRs documentation for analog-digital converter.
	sbi(ADCSRA, ADSC);
	loop_until_bit_is_clear(ADCSRA, ADSC);
	
	// Reads the current output from the gyro
	sbi(ADCSRA, ADSC);
	loop_until_bit_is_clear(ADCSRA, ADSC);
	
	// Since the ad converted value is saved in 2 8-bit registers
	// we have to read the first 8 low bits to not corrupt the read.
	int low = ADCL;
	
	// Shift the 2 high bits 8 steps, and then add the low bits
	return (ADCH << 8) | low;	
}

void reflex_run(int channel_select)
{
	//Sends channel data on PB1-PB4 and enable signal on PB5.
	PORTB = (channel_select<<1) | (1<<PB5);
	//int testing = 0b00000111111;
	//Receives response data on PB0
	_delay_ms(20);
	int compareData = adcRead();
	// Saves the values of sensor 1 and 11 in seperate variables, used for the display and to calibrate the threshold
	//if (reflexValues[channel_select] < threshold[channel_select]){
		reflexValues[channel_select] = compareData;
	//}
	if (compareData < threshold[channel_select]){
		reflex_data &= ~(1 << channel_select);
	}
	else{
		reflex_data |= (1 << channel_select);
	}
	
	/*
	reflex_data[channel_select] = (PINB & (1<<PB0));	
	*/
}

void reflex_run_all(){
	for (int i = 10; i >= 0; i--)
	{
		reflex_run(i);
	}
}


void calibrateReflexSensors(){	
	// Set threshold to the value in the middle of the values from sensor 1 and 11
	//threshold = (reflexValue1 + reflexValue11)/2;	
}