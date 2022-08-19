/*
   plan to use this as main file and calling headers
   to carry out the task
*/
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include "BME280.h"
#include "DS18B20.h"
#include "displayLCD.h"


void setup() {
  // set baud rate
  Serial.begin(9600);
}

void loop() {
  // loop thru these functions
  // declare BME sensors I2C address and call the
  // printToSerial function
  BME b(0x77);
  b.printBMEToSerial();

  // printToSerial function for DS18B20 sensor
  //DS18B20 a();
  //a.printDSToSerial();

  // DS.printDSToSerial();

  // printToLCD function for our sensors
  LCD a(0x27);
  a.displayLCD();
  delay(1000);
}
