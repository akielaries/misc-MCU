
//#include <Wire.h>
//#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

// use this for SIP protocol
/*
#define BME_SCK 21
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10
*/
#define SEALEVELPRESSURE_HPA (1013.25)

// use I2C protocol
Adafruit_BME280 bme;

// Use hardware SPI
//Adafruit_BME280 bme(BME_CS); 
// Use software SPI
//Adafruit_BME280 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  // hardware address defined here
  if (!bme.begin(0x77)) {
    Serial.println("Could not find a valid BME280 sensor, check wiring or default address!");
    while (1);  
  }

}

// print our values
void loop() {
  // put your main code here, to run repeatedly:
  
  // display temperature in celsius and degrees F
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
  delay(9900);

}
