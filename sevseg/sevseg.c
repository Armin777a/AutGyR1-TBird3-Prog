/*
 * sevseg.c
 *
 * Created: 11/24/2022 11:15:04 AM
 *  Author: Armin
 */ 

#include "sevseg.h"

// Seven segment display global variables
uint8_t sevseg_digits[4] = {};
uint8_t sevseg_digsel = 0;



// Converts a 4 digit integer into 4 different digits
void SevsegOut(uint16_t val) {
	// Int to digits
	sevseg_digits[0] = val % 10;
	sevseg_digits[1] = (val/10) % 10;
	sevseg_digits[2] = (val/100) % 10;
	sevseg_digits[3] = (val/1000) % 10;
	
	// Send to 7seg
	sevseg_digsel = (sevseg_digsel+1)%4;
	SevsegPort(sevseg_digits[sevseg_digsel], sevseg_digsel);
}

// Writes out the input to seven segment dispaly
void SevsegPort(uint8_t num, uint8_t digitsel) {
	// Error handling
	if (digitsel > 3) {
		return;
	}
	if (num > 9) {
		return;
	}
	
	// PA7 - Enable
	// PA6 - :
	// PA4-5 - Select digit
	//				11 - dig3
	//				10 - dig2
	//				01 - dig1
	//				00 - dig0
	
	PORTA = 0x80 | (digitsel)<<4 | num;	// Write out to 7seg
}
