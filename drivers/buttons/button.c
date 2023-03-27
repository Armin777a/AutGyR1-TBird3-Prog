#include "button.h"


// ==================== Global variables ====================

void (*ButtonCallback[5])(void) = {0};	// Function pointer array
uint8_t pressedFlag = 0;				// Flag for the pressed button

// Matrix keys			        0   1   2   3   4   5   6   7   8   9   *   #
unsigned char MatrixKeys[12] = {69, 14, 13, 11, 22, 21, 19, 38, 37, 35, 70, 67};
uint8_t SizeOfMatrixKeys = sizeof(MatrixKeys) / sizeof(MatrixKeys[0]);		// Size of the MatrixManager array
uint8_t MatrixInput = 12;		// Value from the matrix keyboard (0-11)



// ==================== Functions for the push buttons ====================

// Initialize one push button
void InitButton (uint8_t button, void (*callback)(void)) {
	ButtonCallback[button-1] = callback;	// Set the function pointer				
}


// Run the push button functions
void ButtonFunctionRun(uint8_t button) {
	pressedFlag = 1;						// Set the pressed flag

	if(ButtonCallback[button-1] != 0){		// Check if the function pointer is not null
		ButtonCallback[button-1]();			// Run the function
	}
}


// Button manager with function pointer
void ButtonManagerFunctionCall() {

	if(!(PING & 0x1F)){						// Check if no button is pressed
		if (pressedFlag) {					// Check if a button was pressed
			pressedFlag = 0;				// Clear the pressed flag
		}
		return;								// Return from the function
	}

	if (pressedFlag) {						// Check if a button was pressed
		return;								// Return from the function
	}

	switch(PING & 0x1F){					// Check witch button is pressed			
		case 0x01:
			ButtonFunctionRun(1);
			break;
		case 0x02:
			ButtonFunctionRun(2);
			break;
		case 0x04:
			ButtonFunctionRun(3);
			break;
		case 0x08:
			ButtonFunctionRun(4);
			break;
		case 0x10:
			ButtonFunctionRun(5);
			break;
		default:
			break;
	}
}



// ==================== Functions for the matrix keyboard ====================

uint8_t MatrixManager() {
	uint8_t row = 0x08;		// Elso sor cimzese
	uint8_t read = 0;
	uint8_t i = 0;

	while(1) {
		PORTC &= 0x80;				// Clear the output
		PORTC |= row;				// Set the first row
		_delay_us(10);				// Wait for the output to settle
		read = PINC & 0x7F;			// Read the coulmn
		
		i = 0;

		// Check if the read value is in the MatrixKeys array
		while (i < SizeOfMatrixKeys) {
			if (MatrixKeys[i] == read) {
				return i;
			}
			i++;
		}
		
		// If the row is the last one
		if (row == 0x40) {
			break;				// Break the while loop
		} else {
			row = row << 1;		// Shift the row
		}
	}
	
	// Ha nincs találat
	return 12;
}





// ==================== Legacy ====================

// Return the pressed button number
uint8_t ButtonManager() {
	if(PING & 0x1F){
		switch(PING & 0x1F){
			case 0x01:
				return 1;
				break;
			case 0x02:
				return 2;
				break;
			case 0x04:
				return 3;
				break;
			case 0x08:
				return 4;
				break;
			case 0x10:
				return 5;
				break;
		}
	}
	
	return 0;
}
