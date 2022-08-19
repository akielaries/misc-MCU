#include <OneWire.h>
#include <DallasTemperature.h>



// defines analog pin we will be reading from
#define ONE_WIRE_BUS 8

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

float celsius = 0;
float fahrenheit = 0;

void setup() {
  // put your setup code here, to run once:
  sensors.begin();
  Serial.begin(9600);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  sensors.requestTemperatures();

  celsius = sensors.getTempCByIndex(0);
  fahrenheit = sensors.toFahrenheit(celsius);

  Serial.print(celsius);
  Serial.print(" C ");
  Serial.print(fahrenheit);
  Serial.println(" F");
  delay(1000);
}
