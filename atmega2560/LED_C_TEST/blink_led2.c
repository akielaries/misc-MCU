#include <avr/io.h>
#include <util/delay.h>

int main(void) {
    // Set Pin 7 (Arduino Mega Pin 13) as an output
    DDRB |= (1 << PB7);

    while (1) {
        // Toggle Pin 7
        PORTB ^= (1 << PB7);
        _delay_ms(1250); // Delay for 500 milliseconds
    }

    return 0;
}
