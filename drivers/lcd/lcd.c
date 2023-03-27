// Header files
#include "lcd.h"



// ===============================================
// =                    LCD                     =
// ===============================================


// LCD init
void LCD_Initialization() {
	// PIN ir�nyok be�ll�t�sa: OUT (minden)
	DDR_LCD_RS   |= 1<<PIN_LCD_RS;
	DDR_LCD_RW   |= 1<<PIN_LCD_RW;
	DDR_LCD_E    |= 1<<PIN_LCD_E;
	DDR_LCD_DATA |= MASK_H_LCD_DATA;
	
	// DATA <- 0x20
	PORT_LCD_DATA &= MASK_L_LCD_DATA;		// Ne irjunk fel�l semmit
	PORT_LCD_DATA |= 0x20;
	
	// 5x lcd_clk
	LCD_Clock();
	LCD_Clock();
	LCD_Clock();
	LCD_Clock();
	LCD_Clock();
	
	// 5x 0x28 cmd - 4bit, 2rows, 5x8dots
	LCD_SendInstruction(LCD_4BIT_MODE | LCD_2_ROWS | LCD_FONT_5x8);
	LCD_SendInstruction(LCD_4BIT_MODE | LCD_2_ROWS | LCD_FONT_5x8);
	LCD_SendInstruction(LCD_4BIT_MODE | LCD_2_ROWS | LCD_FONT_5x8);
	LCD_SendInstruction(LCD_4BIT_MODE | LCD_2_ROWS | LCD_FONT_5x8);
	LCD_SendInstruction(LCD_4BIT_MODE | LCD_2_ROWS | LCD_FONT_5x8);
	
	
	// LCD ON
	// LCD_OFF: 0x08        LCD_ON+CUR_OFF: 0x0C        LCD_ON+CUR_ON: 0x0E        LCD_ON+CUR_ON+BLK: 0x0F
	LCD_SendInstruction(LCD_CURSOR_BLINK);
	
	LCD_DisplayClear();
}


// Send a byte to the lcd to be displayed
void LCD_SendData(uint8_t data) {
	// RS <- 1
	SETBIT(PORT_LCD_RS, PIN_LCD_RS);
	
	// R/!W <- 0
	// CLRBIT(PORT_LCD_RW, PIN_LCD_RW);
	
	// Send the data
	LCD_Send8bitsIn4bitMode(data);
	// Check the busy flag
	LCD_CheckBusyFlag();
}


// Send an instruction to the lcd
void LCD_SendInstruction(uint8_t data) {
	// RS <- 0
	CLRBIT(PORT_LCD_RS, PIN_LCD_RS);
	
	// R/!W <- 0
	//CLRBIT(PORT_LCD_RW, PIN_LCD_RW);
	
	// Send the data
	LCD_Send8bitsIn4bitMode(data);
	// Check the busy flag
	LCD_CheckBusyFlag();
}


// Send th data to the lcd (4 bit mode)
void LCD_Send8bitsIn4bitMode(uint8_t data) {
	
	// Send upper bits
	// -------------------------------
	// Set E
	SETBIT(PORT_LCD_E, PIN_LCD_E);
	// Send data to LCD
	LCD_SetLowData(data & MASK_H_LCD_DATA);
	// Delay
	_delay_us(0.5);
	// Clear E	
	CLRBIT(PORT_LCD_E, PIN_LCD_E);
	//Delay
	_delay_us(0.5);


	// Send lower bits
	// -------------------------------
	// Set E
	SETBIT(PORT_LCD_E, PIN_LCD_E);
	// Send data to LCD
	LCD_SetLowData(data << 4);
	// Delay
	_delay_us(0.5);
	// Clear R
	CLRBIT(PORT_LCD_E, PIN_LCD_E);
	//Delay
	_delay_us(0.5);
}


// Clear the data bits but only if its one
void LCD_SetLowData(uint8_t data) {
	// Clear bits Data Port 7-4
	CLRBIT(PORT_LCD_DATA, LCD_DATA7);
	CLRBIT(PORT_LCD_DATA, LCD_DATA6);
	CLRBIT(PORT_LCD_DATA, LCD_DATA5);
	CLRBIT(PORT_LCD_DATA, LCD_DATA4);
	
	// Set the Data Port bit if is it in the parameter
	if (data & 0x80) { SETBIT(PORT_LCD_DATA, LCD_DATA7); }
	if (data & 0x40) { SETBIT(PORT_LCD_DATA, LCD_DATA6); }
	if (data & 0x20) { SETBIT(PORT_LCD_DATA, LCD_DATA5); }
	if (data & 0x10) { SETBIT(PORT_LCD_DATA, LCD_DATA4); }
}


// E 0__|1|__0
void LCD_Clock() {
	// E <- 0
	PORT_LCD_E &= ~(1<<PIN_LCD_E);
	_delay_ms(3);
	
	// E <- 1
	PORT_LCD_E |= (1<<PIN_LCD_E);
	_delay_ms(3);
	
	// E <- 0
	PORT_LCD_E &= ~(1<<PIN_LCD_E);
	_delay_ms(3);
}


// Send a string to the cursor position
void LCD_SendString(char* p) {
	while(*p){				// While the pointer is not null
		LCD_SendData(*p);	// Send the pointers data
		p++;				// Increment the pointer
	}
}


// Send a string to a specific line
void LCD_SendStringToLine(char* str, uint8_t line) {
	uint8_t counter = 0;
	
	LCD_SetCursorLine(line);
	
	while ((counter < 16) && *str) {
		LCD_SendData(*str);
		str++;
		counter++;
	}
}


// Sets the cursor to one of the four lines
void LCD_SetCursorLine(uint8_t line) {
	LCD_SetCursorPos(line, 0);
}


// Sets the cursor position
void LCD_SetCursorPos(uint8_t line, uint8_t column) {
	LCD_SendInstruction(0x80 | (LCD_GetLineAddres(line) + column));
}


// Returns the address of the line in the LCD
uint8_t LCD_GetLineAddres(int row) {
	switch (row) {
		case 0:
			return 0x00;
			break;
		case 1:
			return 0x40;
			break;
		case 2:
			return 0x10;
			break;
		case 3:
			return 0x50;
			break;
	}
	return 0;
}


// Checks the busy flag and waits until its cleared
void LCD_CheckBusyFlag() {
	uint8_t input = 0;
	
	// Clear data pins as input
	LCD_ClearDDR_DATA4to7();
	// Set pull-up resistors for data pins
	LCD_SetPORT_DATA4to7();
	
	// clear RS
	CLRBIT(PORT_LCD_RS, PIN_LCD_RS);
	// Set RW - read instruction
	SETBIT(PORT_LCD_RW, PIN_LCD_RW);
	
	
	while (1) {
		// Read upper bits
		// -------------------------------
		// Set E
		SETBIT(PORT_LCD_E, PIN_LCD_E);
		// Delay
		_delay_us(0.5);
		// Read upper bits
		input = PIN_LCD_DATA;
		// Clear E
		CLRBIT(PORT_LCD_E, PIN_LCD_E);
		// Delay
		_delay_us(0.5);
			
		// Read Lower bits
		// -------------------------------
		// Set E
		SETBIT(PORT_LCD_E, PIN_LCD_E);
		// Delay
		_delay_us(0.5);
		// Read Lower bits
		input |= PIN_LCD_DATA >> 4;
		// Clear E
		CLRBIT(PORT_LCD_E, PIN_LCD_E);
		// Delay
		_delay_us(0.5);
			
		// Check if bit7 is cleared
		if (!(input & (1 << LCD_DATA7))) {
			// If Busy Flag is cleared break from loop
			break;
		}
	}
	
	 // Clear RW
	 CLRBIT(PORT_LCD_RW, PIN_LCD_RW);
	 
	// Set data pins as output
	LCD_SetDDR_DATA4to7();
} 



// ================================
// Supplemental LCD Functions
// ================================


// Clear LCD
void LCD_DisplayClear() {
	LCD_SendInstruction(LCD_DISP_CLEAR);
	LCD_SendInstruction(LCD_RETURN_HOME);
}


// Display on
void LCD_DisplayOn() {
	LCD_SendInstruction(LCD_DISP_ON);
}


// Turns the cursor on
void LCD_CursorOn() {
	LCD_SendInstruction(LCD_CURSOR_ON);
}


// Turns the cursor off
void LCD_CursorOff() {
	LCD_SendInstruction(LCD_CURSOR_OFF);
}


// Turns the cursor blinking on
void LCD_CursorBlink() {
	LCD_SendInstruction(LCD_CURSOR_BLINK);
}


// Set the data pins
void LCD_SetPORT_DATA4to7() {
	// Set DB4-DB7
	SETBIT(PORT_LCD_DATA, LCD_DATA4);
	SETBIT(PORT_LCD_DATA, LCD_DATA5);
	SETBIT(PORT_LCD_DATA, LCD_DATA6);
	SETBIT(PORT_LCD_DATA, LCD_DATA7);
}


// Clear data pins as input
void LCD_ClearDDR_DATA4to7() {
  // set DB4-DB7
  CLRBIT(DDR_LCD_DATA, LCD_DATA4);
  CLRBIT(DDR_LCD_DATA, LCD_DATA5);
  CLRBIT(DDR_LCD_DATA, LCD_DATA6);
  CLRBIT(DDR_LCD_DATA, LCD_DATA7);
}


// Set data pins as output
void LCD_SetDDR_DATA4to7() {
	// Set DB7-DB4 as output
	SETBIT(DDR_LCD_DATA, LCD_DATA4);
	SETBIT(DDR_LCD_DATA, LCD_DATA5);
	SETBIT(DDR_LCD_DATA, LCD_DATA6);
	SETBIT(DDR_LCD_DATA, LCD_DATA7);
}