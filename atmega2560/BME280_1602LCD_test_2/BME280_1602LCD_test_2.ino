/*
   Read temp, pressure, altitude and humidity from BME280 sensor
   and display the results on a 1602 LCD module using I2C as well
   as the serial monitor where I will later implement capturing data
   from and storing elsewhere
*/
#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <SPI.h>
//#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <LiquidCrystal_I2C.h> 
    

// flagstaff atmospheric pressure in hectopascals
#define SEALEVELPRESSURE_HPA (1013.25)
// define digital pin from arduino to read from
#define ONE_WIRE_BUS 8
// OneWire instance communicating with the defined variable
OneWire oneWire(ONE_WIRE_BUS);
// passing OneWire ref to DallasTemp library
DallasTemperature sensors(&oneWire);
// I2C protocol for BME280
Adafruit_BME280 bme;
LiquidCrystal_I2C lcd(0x27, 16, 02);
// LiquidCrystal_I2C lcd(0x27, 20, 04);

// defining temperature vals for DS18B20 temperature sensor
float celsius = 0;
float fahrenheit = 0;
// define delay time (unecessary declaration)
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
  for (int i = 0; i < 3; i++) {
    lcd.backlight();
    delay(250);
    lcd.noBacklight();
    delay(250);
  }
  lcd.backlight();
}
// print values with delay in between them
void loop() {
  // print to serial monitor for export
  printToSerial();
  // print temp and press to LCD first, delaydetect d1 mini pro , then clear screen
  printTemperature();
  printPressure();
  delay(delayTime);
  lcd.clear();
  // print alt and hum second, delay, clear screen
  printAltitude();
  printHumidity();
  delay(delayTime);
  lcd.clear();
}
// print temperature
void printTemperature() {
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print((bme.readTemperature() * 9 / 5) + 32);
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

void printToSerial() {
  // initialize variables from DS18B20 sensor
  sensors.requestTemperatures();
  celsius = sensors.getTempCByIndex(0);
  fahrenheit = sensors.toFahrenheit(celsius);
  
  // from DS18B20 sensor display the following
  Serial.println("From DS18B20 sensor: ");
  Serial.print("Temperature = ");
  Serial.print(fahrenheit);
  //Serial.print(fahrenheit - 1);
  Serial.print("*F(");
  Serial.print(celsius);
  Serial.println("*C)");
  Serial.println();
  
  // from BME280 sensor display the following:
  // display temperature in celsius and degrees F
  Serial.println("From BME280 sensor: ");
  Serial.print("Temperature = ");
  Serial.print((bme.readTemperature() * 9/5) + 32);
  Serial.print("*F(");
  Serial.print(bme.readTemperature());
  Serial.println("*C)");
  
  // display pressure in Hectopascals
  Serial.print("Pressure = ");
  Serial.print(bme.readPressure() / 100.0F);
  Serial.println("hPa");

  // display altitude in ft calculated from sealevel pressure
  Serial.print("Approximate Altitude = ");
  Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA) * 3.281);
  Serial.println("ft");
  
  // humidity in %
  Serial.print("Humidity = ");
  Serial.print(bme.readHumidity());
  Serial.println("%");

  // 10 second interval
  Serial.println();
  Serial.print("Temperature difference of: ");
  Serial.print(fahrenheit - ((bme.readTemperature() * 9/5) + 32));
  Serial.print("*F (");
  Serial.print(celsius - bme.readTemperature());
  Serial.println("*C)");

  Serial.println();
  
}
