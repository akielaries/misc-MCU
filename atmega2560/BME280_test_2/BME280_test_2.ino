/*
 * Read temp, pressure, altitude and humidity from BME280 sensor
 * and display the results on a 1602 LCD module using I2C
 */

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <LiquidCrystal_I2C.h>

#define SEALEVELPRESSURE_HPA (1037.5895)

Adafruit_BME280 bme; // I2C
LiquidCrystal_I2C lcd(0x27, 16, 02);

unsigned long delayTime;

void setup() {
  Serial.begin(9600);
  bool status;
  
  // default settings
  if (!bme.begin(0x77)) {
    Serial.println("Could not find a valid BME280 sensor, check wiring or default address!");
    while (1);  
  }
  // set delay time
  delayTime = 5000; 
  // initialize LCD screen
  lcd.init();
  // flash backlight 3 times on start
  for(int i = 0; i< 3; i++) {
    lcd.backlight();
    delay(250);
    lcd.noBacklight();
    delay(250);
  }
  lcd.backlight();
}
// print values with delay in between them
void loop() { 
  printTemperature();
  printPressure();
  delay(delayTime);
  lcd.clear();
  printAltitude();
  printHumidity();
  delay(delayTime);
  lcd.clear();
}
// print temperature
void printTemperature() {
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print((bme.readTemperature() * 9/5) + 32);
  lcd.print(" F");
}
// print pressure
void printPressure() {
  lcd.setCursor(0, 1);
  lcd.print("Press: ");
  lcd.print(bme.readPressure() / 100.0F);
  lcd.print("hPa");
}
// print altitude
void printAltitude() {
  lcd.setCursor(0, 0);
  lcd.print("Alt: ");
  lcd.print(bme.readAltitude(SEALEVELPRESSURE_HPA) * 3.281);
  lcd.print(" ft");
}
// print relative humidity
void printHumidity() {
  lcd.setCursor(0, 1);
  lcd.print("RH: ");
  lcd.print(bme.readHumidity());
  lcd.print("%");

}

/*
void printValues() {
  lcd.print("Temperature = ");
  lcd.print((bme.readTemperature() * 9/5) + 32);
  lcd.print("*F(");
  lcd.print(bme.readTemperature());
  lcd.println("*C)");
}

*/
