/*
 * header file for corresponding .cpp file to
 * display sensor values to connect LCD screen
 */
#ifndef displayLCD_h
#define displayLCD_h

#include <Arduino.h>

class LCD {
  public:
    LCD(int LCDaddr);
    void displayLCD();
};

#endif
