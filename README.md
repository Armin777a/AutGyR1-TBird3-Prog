# OE-KVK T-Bird Driver Library for ATmega128 and ATmega64

This is a collection of drivers for the AVR ATmega128 microcontroller, developed for use with a development board. The drivers included in this library are:

- ADC
- Buttons
- Fifo
- Init
- LCD
- Sevseg
- UART

Each driver is contained in its own folder, with its own header and source file. 

## ADC

The ADC driver initializes the ADC and allows you to start it by inputting its channel. You can also enable interrupts so that while the conversion works you don't need to wait. Sample code is provided in the `.h` header file.

## Buttons

The Buttons driver provides functions for the 5 buttons on the board and the matrix keyboard. There are two types of function to use the buttons. One of them uses function pointers. You need to initialize each button and give them a function that will run when the button is pressed. There are also legacy codes which will return the pressed button's value/number.

## Fifo

The Fifo driver provides a simple dynamic ring FIFO that stores an array and its size. You can use functions to put or get values from it.

## Init

The Init driver initializes ports and timers. By default, all the timer initializations are commented out.

## LCD

The LCD driver provides functions for writing on different lines, setting the cursor settings, and clearing the screen. It watches the busy flag so it is faster than using delays.

## Sevseg

The Sevseg driver provides a driver for the seven-segment display. It needs a 16-bit number as an input and it needs to be run frequently.

## UART

The UART driver initializes UART 0 and 1. There are commands to clear the terminal and send some escape codes.

## Contributing

Contributions to this library are welcome! If you'd like to add a new driver or improve an existing one, please create a pull request with your changes.

## License

This library is released under the [MIT License](LICENSE).
