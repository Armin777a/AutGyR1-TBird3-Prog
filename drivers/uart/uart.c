/*
 * uart.c
 *
 * Created: 11/24/2022 11:17:16 AM
 *  Author: Armin
 */

#include "uart.h"

// Sting küldés
void UsartTransmitString(char* p) {
	while (*p) {
		UsartTransmit(*p);
		p++;
	}
}



// UART küldés
void UsartTransmit(char data) {
	// Wait for empty transmit buffer
	while (!(UCSR0A & (1<<UDRE0)));
	
	// Put data into buffer, sends the data
	UDR0 = data;
}



// UART fogadás
unsigned char UsartReceive() {
	// Wait for data to be received
	while(!(UCSR0A & (1<< RXC0)));
	
	// Get and return received data from buffer
	return UDR0;
}



// UART Inicializálás
void UsartInit(unsigned int ubrr) {
	// Set baud rate
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	
	// Enable receiver and transmitter
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	
	// Set frame format: 8data, 2stop bit
	UCSR0C = (1<<USBS0)|(3<<UCSZ00);
	
	// Enable usart interrupts
	UCSR0B |= (0 << TXEN0) | (0 << RXEN0) | (1 << RXCIE0);
}

void UsartClearTerminal() {
	UsartTransmitString("\e[2J\e[0;0H");
}

void UsartClearLine() {
	UsartTransmitString("\e[2K");
}

void UsartMoveCursor(uint8_t line, uint8_t position) {
	UsartTransmit(27);
	UsartTransmit('[');
	UsartTransmit(line + '0');
	UsartTransmit(';');
	UsartTransmit(position + '0');
	UsartTransmit('H');
}

void UsartCursorBlinkOn() {
	UsartTransmitString("\e[?25h");
}

void UsartCursorBlinkOff() {
	UsartTransmitString("\e[?25l");
}