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

	// Timer 0 initialization
/* 	TCCR0 = (0<<WGM01) | (0<<WGM00) | (1<<CS02) | (0<<CS01) | (0<<CS00);
	TIMSK |= (0<<OCIE0) | (1<<TOIE0); */


	// Timer 2 initialization
/* 	TCCR2 = (0<<WGM21) | (0<<WGM20) | (1<<CS22) | (0<<CS21) | (0<<CS20);
	TIMSK |= (0<<OCIE2) | (1<<TOIE2); */
	
	
	
	// Timer 1 initialization
	// TIMER1 CTC COMPA 256 10Hz - 100ms
/* 	TCCR1A = (0<<WGM11) | (0<<WGM10);
	TCCR1B = (0<<WGM13) | (1<<WGM12) | (1<<CS12) | (0<<CS11) | (0<<CS10);
	TIMSK |= (1<<OCIE1A);
	OCR1A = 62500-1; */


	// Timer 3 initialization
	// TIMER3 CTC COMPA 256 10Hz - 100ms
/* 	TCCR3A = (0<<WGM31) | (0<<WGM30);
	TCCR3B = (0<<WGM33) | (1<<WGM32) | (1<<CS32) | (0<<CS31) | (0<<CS30);
	TIMSK |= (1<<OCIE3A);
	OCR3A = 62500-1; */

	sei();
}