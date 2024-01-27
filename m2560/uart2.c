#include <avr/io.h>
#include <stdio.h>
#include <string.h>
#include <util/delay.h>

#define F_CPU 16000000UL // Define the clock frequency

void USART_init() {
    // Set baud rate: 9600 baud, assuming F_CPU = 16MHz
    UBRR0H = (uint8_t)(103 >> 8);
    UBRR0L = (uint8_t)(103);

    // Enable transmitter and receiver
    UCSR0B = (1 << TXEN0) | (1 << RXEN0);

    // Set frame format: 8 data bits, 1 stop bit, no parity
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void USART_transmit_char(char data) {
    // Wait for empty transmit buffer
    while (!(UCSR0A & (1 << UDRE0)))
        ;

    // Put data into buffer, sends the data
    UDR0 = data;
}

void USART_transmit_string(const char *str) {
    // Transmit each character in the string
    for (size_t i = 0; i < strlen(str); ++i) {
        USART_transmit_char(str[i]);
    }
}

int main(void) {
    USART_init();

    while (1) {
        const char *message = "Hello World!\n";
        USART_transmit_string(message);
        printf("hello");

        _delay_ms(1000); // Delay for 1 second
    }

    return 0;
}
