
# UART_Firmware_Task
UART communication using an Arduino to: - Send data from a PC to the MCU (Arduino Uno) via UART. - Store the data in the internal EEPROM of the MCU. - Send the data back to the PC via UART. - Measure and display real-time transmission and reception speeds in bits per second (bps).
# UART Firmware 

This project demonstrates UART communication using an Arduino to:
- Send data from a PC to the MCU (Arduino Uno) via UART.
- Store the data in the internal EEPROM of the MCU.
- Send the data back to the PC via UART.
- Measure and display real-time transmission and reception speeds in bits per second (bps).

## Features
- Bidirectional UART communication.
- Data storage in EEPROM.
- Real-time speed monitoring.

## Setup Instructions
1. Open the `UART_Firmware.ino` file in the Arduino IDE.
2. Upload the code to an Arduino Uno.
3. Use the Serial Monitor at 2400 baud rate to test communication.
4. View live speed data on the Serial Monitor.

## Circuit Details
- **UART Communication:** Handled via USB to Serial.
- **EEPROM:** Internal EEPROM of Arduino Uno.
- Optional: Push button to manually trigger transmission.

## Simulation
- The project can be simulated using Tinkercad.

## Author
Samidha Sudesh Chari

