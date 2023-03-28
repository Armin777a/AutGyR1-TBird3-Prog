#include <avr/io.h>
#include "drivers/drivers.h"
#include <util/delay.h>

#define CLOCK_HHMM			1
#define CLOCK_MMSS			2
#define CLOCK_HOUR			0
#define CLOCK_MINUTE		1
#define CLOCK_SECOND		2

// Normal clock funcions
void ClockStep();							// This makes the clock tick, needs to run every second					
void SendClockUart();						// Sends the current time to UART

// Set the clock
void PrintSetClock(uint8_t select);
void SetClockUsart();
void SetClockData(uint8_t select);

void ButtonController();					// Polls the buttons

// Stopper functions
uint16_t GetStopperNumber(uint8_t select);	// Returns the clocks value in 4 digits (HH:MM or MM:SS)
void StopperStep();
void StopperStop();
void StopperStart();
void StopperReset();


// FOR DEBUG REMOVE
uint8_t leds = 0;

// Normal clock variables
uint8_t ClockData[3] = {12,  34,  56};
char UartClockData[] = "##:##:##\r";
uint8_t IsClockEnabled = 1;

// Clock set variables
char* SetClockMenu[] = {
	"Adja meg az orat: \r\n\n",
	"Adja meg a percet: \r\n\n",
	"Adja meg a masodpercet: \r\n\n"
};
char UsartInput = 0;


// Stopper variables
uint8_t StopperData[2] = {0, 0};
uint8_t IsStopperEnabled = 0;


// Button variables
uint8_t ButtonInput = 0;
uint8_t ButtonHold = 0;
uint8_t ButtonNewData = 0;
uint8_t CurrentMode = 0;



int main(void) {
	
	InitPorts();
	InitTimer();
	Usart0Init(MYUBRR);
	Usart0CursorBlinkOff();
	Usart0ClearTerminal();

    while (1) {
    }
}


// Timer0 overflow interrupt routine
ISR(TIMER2_OVF_vect) {
	SevsegOut( GetStopperNumber(CLOCK_MMSS) );
	ButtonController();
}


ISR(TIMER1_COMPA_vect) {
	sei();	// Interruptban is enged�lyezz�k az interruptot
	
	if (IsClockEnabled) {
		ClockStep();
		SendClockUart();
	}
	
	if (IsStopperEnabled) {
		StopperStep();
	}
	
	LedOut(leds);
	leds ^= 0x01;
}


ISR(USART0_RX_vect) {
	UsartInput = UDR0;
	SetClockUsart();
}



uint8_t SetClockValue = 0;
uint8_t SetClockDigit1 = 0;
uint8_t SetClockDigit2 = 0;
uint8_t SetClockCounter = 0;
uint8_t SetClockState = 0;

void SetClockUsart() {
	uint8_t input = UsartInput - '0';
	
	if (IsClockEnabled) {
		return;
	}
	
	if (0 <= input && input <= 9) {
		if (SetClockCounter < 2) {
			switch (SetClockCounter) {
				case 0:
					SetClockDigit2 = input;
					break;
				case 1:
					SetClockDigit1 = SetClockDigit2;
					SetClockDigit2 = input;
					break;
			}
			
			SetClockCounter++;
			Usart0Transmit(UsartInput);
		}
	}
	
	if (UsartInput == '\r') {
		Usart0Transmit('\r');
		
		SetClockValue = SetClockDigit1*10 + SetClockDigit2;
		
		
		if ((SetClockState == 1) && (SetClockValue >= 24)) {
			Usart0MoveCursor(5, 0);
			Usart0TransmitString("ERROR");
			Usart0MoveCursor(3, 0);
			Usart0ClearLine();
		} else if (SetClockValue >= 60) {
			Usart0MoveCursor(5, 0);
			Usart0TransmitString("ERROR");
			Usart0MoveCursor(3, 0);
			Usart0ClearLine();
		} else {
			Usart0ClearTerminal();
			
			SetClockData(SetClockState-1);
			SetClockState++;
			
			if (SetClockState > 3) {
				Usart0ClearTerminal();
				IsClockEnabled = 1;
				CurrentMode = 1;
				SendClockUart();
				Usart0CursorBlinkOff();
			} else {
				PrintSetClock(SetClockState);
				SetClockDigit1 = 0;
				SetClockDigit2 = 0;
			}
		}
		
		SetClockCounter = 0;
		SetClockValue = 0;
	}
	
	if (UsartInput == '\b') {
		if (SetClockCounter) {
			Usart0TransmitString("\b \b");
			switch (SetClockCounter) {
				case 0:
					SetClockDigit1 = 0;
					break;
				case 1:
					SetClockDigit2 = 0;
					break;
			}
			SetClockCounter--;
		}
	}
}




void SetClockData(uint8_t select) {
	if (select > CLOCK_SECOND) {
		return;
	}
	
	ClockData[select] = SetClockValue;
}




void ButtonController() {
	ButtonInput = ButtonManager();
	
	if (ButtonInput) {
		if (!ButtonHold) {
			ButtonHold = 1;
			ButtonNewData = 1;
			CurrentMode = ButtonInput;
		}
	} else {
		ButtonHold = 0;
	}
	
	if (ButtonNewData) {
		ButtonNewData = 0;
		
		switch (CurrentMode) {
			case 1:
				if (!IsClockEnabled) {
					IsClockEnabled = 1;
					SendClockUart();
					Usart0CursorBlinkOff();
				}
				break;
			case 2:
				if (IsClockEnabled) {
					IsClockEnabled = 0;
					SetClockState = 1;
					SetClockDigit1 = 0;
					SetClockDigit2 = 0;
					PrintSetClock(SetClockState);
					Usart0CursorBlinkOn();
				}
				break;
			case 3:
				StopperStart();
				break;
			case 4:
				StopperStop();
				break;
			case 5:
				StopperReset();
				break;
		}
	}
}





void PrintSetClock(uint8_t select) {
	if (select > 3) {
		return;
	}
	
	Usart0TransmitString(SetClockMenu[select-1]);
}






void SendClockUart() {
	UartClockData[0] = (ClockData[CLOCK_HOUR]/10   % 10) + '0';
	UartClockData[1] = (ClockData[CLOCK_HOUR]      % 10) + '0';
	UartClockData[3] = (ClockData[CLOCK_MINUTE]/10 % 10) + '0';
	UartClockData[4] = (ClockData[CLOCK_MINUTE]    % 10) + '0';
	UartClockData[6] = (ClockData[CLOCK_SECOND]/10 % 10) + '0';
	UartClockData[7] = (ClockData[CLOCK_SECOND]    % 10) + '0';
	
	Usart0ClearTerminal();
	Usart0TransmitString(UartClockData);
}






void ClockStep() {
	ClockData[CLOCK_SECOND]++;
	
	if (ClockData[CLOCK_SECOND] > 59) {
		ClockData[CLOCK_SECOND] = 0;
		ClockData[CLOCK_MINUTE]++;
	}
	
	if (ClockData[CLOCK_MINUTE] > 59) {
		ClockData[CLOCK_MINUTE] = 0;
		ClockData[CLOCK_HOUR]++;
	}
	
	if (ClockData[CLOCK_HOUR] > 23) {
		ClockData[CLOCK_HOUR] = 0;
		ClockData[CLOCK_MINUTE] = 0;
		ClockData[CLOCK_SECOND] = 0;
	}
}


void StopperStep() {
	StopperData[1]++;
	
	if (StopperData[1] > 59) {
		StopperData[1] = 0;
		StopperData[0]++;
	}
	
	if (StopperData[0] > 59) {
		StopperData[0] = 0;
	}
	
}




void StopperStop() {
	IsStopperEnabled = 0;
}

void StopperStart() {
	IsStopperEnabled = 1;
}

void StopperReset() {
	StopperStop();
	StopperData[0] = 0;
	StopperData[1] = 0;
	
}



// Returns the clock data array in a 16 bit 4 digit form
uint16_t GetStopperNumber(uint8_t select) {
	uint16_t time = 0;

	time =  StopperData[0] * 100;
	time += StopperData[1];
	
	return time;
}