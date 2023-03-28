#pragma once
#ifndef UART_H_
#define UART_H_

#include <avr/io.h>
#include "../clockfreq.h"

#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1


// For UART0
void Usart0Init(unsigned int ubrr);                         // UART0 initialization
void Usart0Transmit(char data);                             // UART0 Send single char
void Usart0TransmitString(char* p);                         // UART0 Send string
unsigned char Usart0Receive();                              // UART0 Receive single char
void Usart0ClearTerminal();                                 // UART0 Clear terminal
void Usart0ClearLine();                                     // UART0 Clear line
void Usart0MoveCursor(uint8_t line, uint8_t position);      // UART0 Move cursor to line and position
void Usart0CursorBlinkOff();                                // UART0 Cursor blink off
void Usart0CursorBlinkOn();                                 // UART0 Cursor blink on

// For UART1
void Usart1Init(unsigned int ubrr);                         // UART1 initialization
void Usart1Transmit(char data);                             // UART1 Send single char
void Usart1TransmitString(char* p);                         // UART1 Send string
unsigned char Usart1Receive();                              // UART1 Receive single char
void Usart1ClearTerminal();                                 // UART1 Clear terminal
void Usart1ClearLine();                                     // UART1 Clear line
void Usart1MoveCursor(uint8_t line, uint8_t position);      // UART1 Move cursor to line and position
void Usart1CursorBlinkOff();                                // UART1 Cursor blink off
void Usart1CursorBlinkOn();                                 // UART1 Cursor blink on

#endif /* UART_H_ */