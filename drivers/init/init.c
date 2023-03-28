/*
 * init.c
 *
 * Created: 11/24/2022 11:10:19 AM
 *  Author: Armin
 */ 

#include "init.h"


// Port initialization
void InitPorts() {
	DDRA = 0xFF;                        // 7 segment
	DDRB = 0xF0;                        // LED 0-3
	DDRC = 0x78 | 0x80;                 // Matrix + Red LED
	DDRD = 0xF0;                        // LED 4-7
	DDRE = 0x08 | 0x04;					// Green LED + Blue LED
}


// Timer initialization
void InitTimer() {
	TCCR2 = (0<<WGM21) | (0<<WGM20) | (1<<CS22) | (0<<CS21) | (0<<CS20);
	TIMSK |= (0<<OCIE2) | (1<<TOIE2);
	
	
	// Timer 1 1mp-es interrupt
	// TIMER1 CTC COMPA 256 10Hz - 100ms
	TCCR1A = (0<<WGM11) | (0<<WGM10);
	TCCR1B = (0<<WGM13) | (1<<WGM12) | (1<<CS12) | (0<<CS11) | (0<<CS10);
	TIMSK |= (1<<OCIE1A);
	OCR1A = 62500-1;

	sei();
}