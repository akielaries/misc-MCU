/*
 * source files testing displaying sensor values to
 * connect LCD screen using C++
*/ 

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include "displayLCD.h"

LiquidCrystal_I2C lcd(0x27, 16, 02);
/*
LCD::LCD(int LCDaddr) {
    if (!lcd.init(LCDaddr)) {
        Serial.println("Could not find display. Please check wiring.");
        while(1);
    }
}
*/
void LCD::displayLCD() {
    lcd.begin(16,02);
    for (int i = 0; i < 3; i++) {
        lcd.backlight();
        delay(250);
        lcd.noBacklight();
        delay(250);
    }
    lcd.backlight();

    Serial.println("Debug statement");
}
