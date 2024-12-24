#include <stdint.h>
#include <stdbool.h>
#include "microcontroller_uart.h"  // Platform-specific UART functions
#include "microcontroller_eeprom.h" // Platform-specific EEPROM functions

#define BAUD_RATE 2400
#define EEPROM_SIZE 1024
#define LED_PIN 13 

void setup_hardware(void);
void receive_data(void);
void send_data_back(void);

int main(void) {
    setup_hardware();  // Initialize UART, EEPROM, and GPIO
    uart_send_string("Ready to receive data...\n");

    while (1) {
        if (uart_data_available()) {
            uart_send_string("Receiving data...\n");
            receive_data();
            uart_send_string("Data stored in EEPROM. Sending it back...\n");
            send_data_back();
        }
    }
}

void setup_hardware(void) {
    uart_init(BAUD_RATE);             // Initialize UART at the specified baud rate
    eeprom_init();                    // Initialize EEPROM (if required)
    gpio_set_pin_mode(LED_PIN, OUTPUT); // Set LED_PIN as output
    gpio_write(LED_PIN, HIGH);        // Turn on LED
}

void receive_data(void) {
    uint16_t eeprom_index = 0;
    uint32_t start_time = get_millis();  // Start time in milliseconds

    while (uart_data_available() && eeprom_index < EEPROM_SIZE) {
        char data = uart_read();         // Read a byte from UART
        eeprom_write(eeprom_index++, data); // Write byte to EEPROM
        delay_ms(10);                   // Simulate EEPROM write time
    }

    uint32_t end_time = get_millis();    // End time
    uint32_t bits_transferred = eeprom_index * 8;  // 8 bits per byte
    float speed = (float)bits_transferred / ((end_time - start_time) / 1000.0);
    uart_send_string("Reception Speed: ");
    uart_send_float(speed);
    uart_send_string(" bps\n");

    eeprom_write(eeprom_index, '\0');   // End marker
}

void send_data_back(void) {
    uint16_t eeprom_index = 0;
    char data;
    uint32_t start_time = get_millis();  // Start time

    while (eeprom_index < EEPROM_SIZE) {
        data = eeprom_read(eeprom_index++);
        if (data == '\0') break;
        uart_write(data);               // Send data via UART
        delay_ms(10);                   // Simulate transmission delay
    }

    uint32_t end_time = get_millis();    // End time
    uint32_t bits_transferred = eeprom_index * 8;  // 8 bits per byte
    float speed = (float)bits_transferred / ((end_time - start_time) / 1000.0);
    uart_send_string("Transmission Speed: ");
    uart_send_float(speed);
    uart_send_string(" bps\n");

    uart_send_string("Data sent back successfully.\n");
}
