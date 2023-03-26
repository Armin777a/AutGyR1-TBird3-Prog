#pragma once
#ifndef UART_H_
#define UART_H_

#include <avr/io.h>
#include "../clockfreq.h"

#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1

void UsartInit(unsigned int ubrr);
void UsartTransmit(char data);
void UsartTransmitString(char* p);
unsigned char UsartReceive();
void UsartMoveCursor(uint8_t line, uint8_t position);
void UsartClearTerminal();
void UsartClearLine();
void UsartCursorBlinkOff();
void UsartCursorBlinkOn();

#endif /* UART_H_ */