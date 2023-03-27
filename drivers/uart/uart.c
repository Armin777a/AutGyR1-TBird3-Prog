// Include header file
#include "uart.h"



// ===============================================
// =                    UART0                    =
// ===============================================


// UART0 initialization
void Usart0Init(unsigned int ubrr) {
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


// UART0 Send single char
void Usart0Transmit(char data) {
	// Wait for empty transmit buffer
	while (!(UCSR0A & (1<<UDRE0)));
	
	// Put data into buffer, sends the data
	UDR0 = data;
}


// UART0 Send string
void Usart0TransmitString(char* p) {
	while (*p) {
		Usart0Transmit(*p);
		p++;
	}
}


// UART0 Receive single char
unsigned char Usart0Receive() {
	// Wait for data to be received
	while(!(UCSR0A & (1<< RXC0)));
	
	// Get and return received data from buffer
	return UDR0;
}


// UART0 Clear terminal
void Usart0ClearTerminal() {
	Usart0TransmitString("\e[2J\e[0;0H");
}


// UART0 Clear line
void Usart0ClearLine() {
	Usart0TransmitString("\e[2K");
}


// UART0 Move cursor to line and position
void Usart0MoveCursor(uint8_t line, uint8_t position) {
	Usart0Transmit(27);
	Usart0Transmit('[');
	Usart0Transmit(line + '0');
	Usart0Transmit(';');
	Usart0Transmit(position + '0');
	Usart0Transmit('H');
}


// UART0 Cursor blink on
void Usart0CursorBlinkOn() {
	Usart0TransmitString("\e[?25h");
}


// UART0 Cursor blink off
void Usart0CursorBlinkOff() {
	Usart0TransmitString("\e[?25l");
}





// ===============================================
// =                    UART1                    =
// ===============================================


// UART1 initialization
void Usart1Init(unsigned int ubrr) {
	// Set baud rate
	UBRR1H = (unsigned char)(ubrr>>8);
	UBRR1L = (unsigned char)ubrr;
	
	// Enable receiver and transmitter
	UCSR1B = (1<<RXEN0)|(1<<TXEN0);
	
	// Set frame format: 8data, 2stop bit
	UCSR1C = (1<<USBS0)|(3<<UCSZ00);
	
	// Enable usart interrupts
	UCSR1B |= (0 << TXEN0) | (0 << RXEN0) | (1 << RXCIE0);
}


// UART1 Send single char
void Usart1Transmit(char data) {
	// Wait for empty transmit buffer
	while (!(UCSR1A & (1<<UDRE0)));
	
	// Put data into buffer, sends the data
	UDR1 = data;
}


// UART1 Send string
void Usart1TransmitString(char* p) {
	while (*p) {
		Usart1Transmit(*p);
		p++;
	}
}


// UART1 Receive single char
unsigned char Usart1Receive() {
	// Wait for data to be received
	while(!(UCSR1A & (1<< RXC0)));
	
	// Get and return received data from buffer
	return UDR1;
}


// UART1 Clear terminal
void Usart1ClearTerminal() {
	Usart1TransmitString("\e[2J\e[0;0H");
}


// UART1 Clear line
void Usart1ClearLine() {
	Usart1TransmitString("\e[2K");
}


// UART1 Move cursor to line and position
void Usart1MoveCursor(uint8_t line, uint8_t position) {
	Usart1Transmit(27);
	Usart1Transmit('[');
	Usart1Transmit(line + '0');
	Usart1Transmit(';');
	Usart1Transmit(position + '0');
	Usart1Transmit('H');
}


// UART1 Cursor blink on
void Usart0CursorBlinkOn() {
	Usart1TransmitString("\e[?25h");
}


// UART1 Cursor blink off
void Usart0CursorBlinkOff() {
	Usart1TransmitString("\e[?25l");
}