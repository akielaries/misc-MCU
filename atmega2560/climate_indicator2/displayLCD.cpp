/*
 * source files testing displaying sensor values to
 * connect LCD screen using C++
*/ 
#include <Arduino.h>
#include <Adafruit_BME280.h>
#include <LiquidCrystal_I2C.h>
#include "BME280.h"
#include "displayLCD.h"

#define SEALEVELPRESSURE_HPA (1013.25)

// define instance of BME in this file
Adafruit_BME280 bme2;

LiquidCrystal_I2C lcd(0x27, 16, 02);
// initialize LCD screen with I2C address and dimensions 16x02
LCD::LCD(int addr, int width, int height) {
    LiquidCrystal_I2C lcd(addr, width, height);
    lcd.init();    
}
/*
// initialize BME sensor for LCD display
BME::BME2(int BMEaddr) {
    if (!bme2.begin(BMEaddr)) {
        Serial.println("Could not find valid instance of BME280 sensor for LCD display");  
        while(1);    
    }  
}
*/
// display to LCD screen
void LCD::main() {                  
        //bme2.begin();
        displayTemp();
        displayPressure();
        delay(5000);
        lcd.clear();
        
        displayAltitude();
        displayHumidity();
        delay(5000);
        lcd.clear();
}


void LCD::initializeLCD() {
    for (int i = 0; i < 1; i++) {
        lcd.backlight();
        delay(150);
        lcd.noBacklight();
        delay(150);
    }
    lcd.backlight();
    
}

void LCD::displayTemp() {
    //bme2.begin();
    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    //lcd.print((bme2.readTemperature() * 9 / 5) + 32);
    lcd.print(" F");
}

void LCD::displayPressure() {
    lcd.setCursor(0, 1);
    lcd.print("Press: ");
    //lcd.print(bme2.readPressure() / 100.0F);
    lcd.print("hPa");
}

void LCD::displayAltitude() {
    lcd.setCursor(0, 0);
    lcd.print("Alt: ");
    //lcd.print(bme2.readAltitude(SEALEVELPRESSURE_HPA) * 3.281);
    lcd.print(" ft");
}

void LCD::displayHumidity() {
    lcd.setCursor(0, 1);
    lcd.print("RH: ");
    //lcd.print(bme2.readHumidity());
    lcd.print("%");
}
