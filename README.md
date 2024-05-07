# EEPROM-Interfacing-Using-8051-Microcontroller

## Overview
This project implements a software-based I2C driver for EEPROM to read/write data from/to the EEPROM. It includes two main functionalities:
1. A one-second counter (8-bit) displayed on a seven-segment display and saved to EEPROM every second.
2. A 32-bit counter saved to EEPROM using 4 adjacent memory locations.

## Features
- Read/write data to/from EEPROM using an I2C driver.
- Display the 8-bit counter on a seven-segment display.
- Store the 32-bit counter in EEPROM across 4 memory locations.
- Preserve counter values between system resets using EEPROM.
- Implement a delay between EEPROM writes to extend EEPROM lifespan.

## Implementation Details
### Counter Functionality
- The one-second counter counts up to 255 and then rolls over to 0.
- The 32-bit counter increments continuously.
- Counter values are displayed on respective displays and saved to EEPROM.
- On system startup, the program checks EEPROM values to determine if it's a new board or if the EEPROM data is legitimate.

### EEPROM Write Delay
- The EEPROM's datasheet provides the number of write cycles.
- To extend EEPROM lifespan to at least 10 years, calculate the delay between EEPROM writes accordingly.

## Dependencies
- Hardware: 8051 Microcontroller with I2C and GPIO interfaces, seven-segment display, EEPROM, LCD display (optional).
- Software: Embedded C programming environment, I2C driver library, seven-segment display driver library, LCD driver library (optional).

## Usage
1. Connect the hardware components as per the provided schematic.
2. Compile and flash the code onto the 8051 microcontroller.
3. Power on the system and observe the counter values on the displays.
4. Reset the board and verify if the counter values remain preserved in EEPROM.

## Contributors
- [Fazal Hameed](https://github.com/fazalhameed) - Project Developer

## License
This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details.
