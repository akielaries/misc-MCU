/*
 library created for flashing morse code
 currently using to test creating arduino libraries
 */

#ifndef Morse_h
#define Morse_h
#include <Arduino.h>

class Morse {
  public:
    Morse(int pin);
    void dot();
    void dash();

  private:
    int _pin;
};

#endif
