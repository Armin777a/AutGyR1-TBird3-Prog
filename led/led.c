/*
 * led.c
 *
 * Created: 11/24/2022 11:13:25 AM
 *  Author: Armin
 */ 

#include "led.h"


// LED manager
void LedOut(uint8_t led) {
	PORTD &= 0x0F;			// Clear the upper 4 bit
	PORTD |= led & 0xF0;		// Set the upper 4 bit
	PORTB &= 0x0F;			// Clear the upper 4 bit
	PORTB |= (led<<4) & 0xF0;	// Shift the lower 4 bits up and set it
}
