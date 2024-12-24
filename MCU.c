#include<stdio.h>
#include<stdint.h>
#include <EEPROM.h> // Includes the EEPROM library for reading from and writing to the EEPROM memory of the Arduino.

#define baudRate 2400   // UART communication speed 2400 bits per second
#define textSize 1500   // Approximate size of the text to be transmitted 
#define eepromSize 1024 // size of the EEPROM for storing data

void setup() {
    Serial.begin(baudRate);                         // Initialize UART with 2400 baud rate 
    Serial.println("Ready to receive data...");     //Sends a message to the Serial Monitor, indicating the MCU is ready to start receiving data.
}

void loop() {
    if (Serial.available() > 0) {
        Serial.println("Receiving data...");
        receiveData();   // Receive data from Serial Monitor and store in EEPROM
        Serial.println("Data stored in EEPROM. Sending it back...");
        sendDataBack();  // Send stored data back to Serial Monitor
    }
}

void receiveData() {
    int eepromIndex = 0;
    unsigned long startTime = millis();  // Start time

    while (Serial.available() > 0 && eepromIndex < EEPROM_SIZE) {
        char data = Serial.read();
        EEPROM.write(eepromIndex++, data);
        delay(10);  // Simulate EEPROM write time
    }

    unsigned long endTime = millis();  // End time
    unsigned long bitsTransferred = eepromIndex * 8;  // 8 bits per byte
    float speed = (float)bitsTransferred / ((endTime - startTime) / 1000.0);  // bps
    Serial.print("Reception Speed: ");
    Serial.print(speed);
    Serial.println(" bps");

    EEPROM.write(eepromIndex, '\0');  // End marker
}

void sendDataBack() {
    int eepromIndex = 0;
    char data;
    unsigned long startTime = millis();  // Start time

    while (eepromIndex < EEPROM_SIZE) {
        data = EEPROM.read(eepromIndex++);
        if (data == '\0') break;
        Serial.write(data);
        delay(10);  // Simulate transmission delay
    }

    unsigned long endTime = millis();  // End time
    unsigned long bitsTransferred = eepromIndex * 8;  // 8 bits per byte
    float speed = (float)bitsTransferred / ((endTime - startTime) / 1000.0);  // bps
    Serial.print("Transmission Speed: ");
    Serial.print(speed);
    Serial.println(" bps");

    Serial.println("\nData sent back successfully.");
}

int main() {
    init();                // Initialize hardware and core libraries
    setup();               // Call user-defined setup() function it only runs once 

    while (true) {         // Infinite loop
        loop();            // Call user-defined loop() function
    }
    return 0;
}