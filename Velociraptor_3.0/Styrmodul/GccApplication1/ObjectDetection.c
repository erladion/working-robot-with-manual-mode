#define F_CPU 14750000
#include <stdbool.h>
#include <avr/delay.h>
#include "Mode.h"

volatile bool pastFirstLine = false;

int activatedSensors(int reflexData, int startIndex, int stopIndex)
{
	int amountActivated = 0;
	int x = startIndex;
	for (x; x < stopIndex; x++) {
		if ((reflexData & (1<<x)) >> x) {
			amountActivated++;
		}
	}
	return amountActivated;
}


bool objectFinder(int reflexData)
{
	// If at least 3 sensors are active, we have found the first tape
	if (activatedSensors(reflexData, 0, 11) < 3) {
		return true;
	}
	return false;
}

/*

			 (Object)
			   XXXX
   -------------------------- (Second line)
				|
				|
				|
				|
				|
				|
				|
				|
				|
				|
				|
				|
   --------------------------- (First line)


*/
void objectCentering(int reflexData)
{	
	// We drive a bit forward at the start to make sure we pass the first line
	if (!pastFirstLine) {
		drive_forward(50);
		_delay_ms(300);
		pastFirstLine = true;
	} else {
		//If a majority of sensors are active == finish line reached.
		if (activatedSensors(reflexData, 8,9) > 0 && activatedSensors(reflexData, 4, 5) > 0) {
			
			current_mode = GRAB;
			return;
		}
		
		//If the center sensor is active, drive forward.
		if (activatedSensors(reflexData, 5, 6)) {
			drive_forward(50);
			
		//If any sensor to the left of the center is active, rotate left.
		} else if (activatedSensors(reflexData, 6, 11) > 0) {
			rotate_left(70);
			
		//If any sensor to the right of the center is active, rotate right.
		} else if (activatedSensors(reflexData, 0, 5) > 0) {
			rotate_right(70);
		}
	}
}
