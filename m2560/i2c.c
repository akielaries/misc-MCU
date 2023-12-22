#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <util/twi.h>

// Define the baud rate and calculate the UBRR value
#define F_CPU 16000000UL
#define UBRR_VALUE ((F_CPU / (16UL * BAUD_RATE)) - 1)

void USART_Init(unsigned int ubrr) {
    // Set baud rate
    UBRR0H = (unsigned char)(ubrr >> 8);
    UBRR0L = (unsigned char)ubrr;
    
    // Enable receiver and transmitter
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);
    
    // Set frame format: 8 data, 1 stop bit
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void USART_Transmit(unsigned char data) {
    // Wait for empty transmit buffer
    while (!(UCSR0A & (1 << UDRE0)))
        ;
    // Put data into buffer, sends the data
    UDR0 = data;
}

void I2C_Init() {
    // Initialize I2C with default settings
    i2c_init();
}

void I2C_ProbeAddresses() {
    uint8_t address;
    uint8_t status;
    
    USART_Transmit('\n');
    USART_Transmit('I');
    USART_Transmit('2');
    USART_Transmit('C');
    USART_Transmit(' ');
    USART_Transmit('A');
    USART_Transmit('d');
    USART_Transmit('d');
    USART_Transmit('r');
    USART_Transmit('e');
    USART_Transmit('s');
    USART_Transmit('s');
    USART_Transmit('e');
    USART_Transmit('s');
    USART_Transmit(':');
    USART_Transmit('\n');
    
    for (address = 1; address <= 127; address++) {
        status = i2c_start(address << 1);
        i2c_stop();
        
        if (status == 0) {
            // Address acknowledged, print it
            USART_Transmit('0' + ((address >> 4) & 0x0F));
            USART_Transmit('0' + (address & 0x0F));
            USART_Transmit(' ');
        }
    }
    
    USART_Transmit('\n');
}

int main(void) {
    // Initialize UART
    USART_Init(UBRR_VALUE);
    
    // Initialize I2C
    I2C_Init();
    
    // Enable global interrupts
    sei();
    
    while (1) {
        // Probe for I2C addresses and print them
        I2C_ProbeAddresses();
        
        // Delay before probing again (adjust as needed)
        _delay_ms(1000);
    }
}

