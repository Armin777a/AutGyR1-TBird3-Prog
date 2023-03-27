#include "led.h"

// LED manager
void LedOut(uint8_t led) {
	PORTD &= 0x0F;			// Clear the upper 4 bit
	PORTD |= led & 0xF0;		// Set the upper 4 bit
	PORTB &= 0x0F;			// Clear the upper 4 bit
	PORTB |= (led<<4) & 0xF0;	// Shift the lower 4 bits up and set it
}

// RGB LED manager (RBG in case of atmega128, RGB in case of atmega64) 
void RgbLed(uint8_t red, uint8_t green, uint8_t blue) {
	if (red) {
		PORTC |= 0x80;
	} else {
		PORTC &= ~0x80;
	}
	
	if (blue) {
		PORTE |= 0x08;
	}else{
		PORTE &= ~0x08;
	}
	
	if (green) {
		PORTE |= 0x04;
	} else {
		PORTE &= ~0x04;
	}
}