/*
 * library used to display the temperature value of 
 * the DS18B20 sensor
*/

/*
#include <Arduino.h>
#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <SPI.h>
// define GIO pin to read from
#define ONE_WIRE_BUS 8

// OneWire instance communicating with defined variable
OneWire oneWire(ONE_WIRE_BUS);
// pass OneWire reference to DallasTemp lib
DallasTemperature sensors(&oneWire);
// define temperature vals for sensor
float celsius = 0;
float fahrenheit = 0;


void DS::printDSToSerial() {
    // initialize vars for DS18B20
    sensors.requestTemperatures();
    celsius = sensors.getTempCByIndex(0);
    fahrenheit = sensors.toFahrenheit(celsius);

    Serial.println("From DS18B20 Sensor: ");
    
    // print temperature values
    Serial.println("From DS18B20 sensor: ");
    Serial.print("Temperature = ");
    Serial.print(fahrenheit);
    //Serial.print(fahrenheit - 1);
    Serial.print("*F(");
    Serial.print(celsius);
    Serial.println("*C)");
    Serial.println();

}
*/
