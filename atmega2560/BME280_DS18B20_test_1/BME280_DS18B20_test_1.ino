#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal_I2C.h>

// use this for SPI protocol using different pins
/*
#define BME_SCK 21
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10
*/
// define sealevel pressure (hectopascals)
#define SEALEVELPRESSURE_HPA (1013.25)
// define digital pin from arduino to read from
#define ONE_WIRE_BUS 8

// OneWire instance communicating with the defined variable
OneWire oneWire(ONE_WIRE_BUS);
// passing OneWire ref to DallasTemp library
DallasTemperature sensors(&oneWire);

// use I2C protocol
Adafruit_BME280 bme;

// to use hardware SPI instead of I2C
// Adafruit_BME280 bme(BME_CS); 
// use software SPI
// Adafruit_BME280 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK);

// defining temperature vals for DS18B20 temperature sensor
float celsius = 0;
float fahrenheit = 0;

void setup() {
  // begin sensor readings
  sensors.begin();
  // initialize LCD
  //lcd.init();
  // set data rate in bits per sec
  Serial.begin(9600);
  
  // hardware address defined here for bme280
  if (!bme.begin(0x77)) {
    Serial.println("Could not find a valid BME280 sensor, check wiring or default address!");
    while (1);  
  }

}

// loop thru and print our values
void loop() {
  // put your main code here, to run repeatedly:
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
  delay(2000);

}
