# Bootloader
Simple bootloader project to flash Blinky-led Application On STM32F401CCU6 MCU

## Overview :
The boot-loader is a small piece of code that has burned on the target manually that initializes the system and loads the main/updated firmware into the flash memory when the system is powered on or reset. Using Python script we can send the hex file of the application over UART to the bootloader to parse each record in the hex file and burn it into flash memory then jump to the new application.

## Features:
- Configure the address of the vector table: 
Depending on the address of the active program.

- Parser: 
After Confirming that the record fetched successfully, it will be parsed by the Parser algorithm to convert it from character form into hexadecimal form.

- Flashing: 
After Confirming that the record parsed successfully, send it to the flash memory interface driver to start flashing it into flash memory.
