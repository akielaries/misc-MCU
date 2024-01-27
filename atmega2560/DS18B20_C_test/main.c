#include <DallasTemperature.h>
#include <OneWire.h>
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>

#define ONE_WIRE_BUS 8
#define MS_DELAY 3000

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&onewire);

float celsius = 0;
float fahrenheit = 0;

void setup() {
    sensors.begin();
    Serial.begin(9600);
}

void loop() {
    sensors.requestTemperatures();

    celsius = sensors.getTempCByIndex(0);
    fahrenheit = sensors.toFahrenheit(celsius);

    printf(celsius);
    printf(" C ");
    printf(fahrenheit);
    printf(" F\n");
    _delay_ms(MS_DELAY);
}
