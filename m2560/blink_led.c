#include <avr/io.h>         // manages I/O of the microcontroller
#include <util/delay.h>     // used for delay

#define MS_DELAY 90

int main (void) {
    /* Setting fifth bit of Data Direction Regigister (DDR) PORTB (DDRB)
     * is setting HIGH to pin 13 
     * Set to one the fifth bit of DDRB 
     * meaning we want to use the pin associated with the fifth bit
     * as output
     * Set digital pin 13 to output mode
    */
    DDRB |= _BV(DDB7);      // _BV = left bit shift 

    while(1) {
        /* Set to one the fifth bit of PORTB one
         * Set to HIGH the pin 13 */
        PORTB |= _BV(PORTB7);
        // wait 3000ms
        _delay_ms(MS_DELAY);

        /* Set to zero the fifth bit of PORTB
         * Set to LOW low pin 13 */
        PORTB &= ~_BV(PORTB7);
        // wait 3000ms
        _delay_ms(MS_DELAY);
            
    }
}

