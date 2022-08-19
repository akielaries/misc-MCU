
/*
 * Wire - I2C Scanner
 *
 * The WeMos D1 Mini I2C bus uses pins:
 * D1 = SCL
 * D2 = SDA
 */

#include <OneWire.h>
#include <Wire.h>
#include <i2cdetect.h>
//#include <Adafruit_ESP8266.h>


//const int SCL_PIN = D1;
//const int SDA_PIN = D2;
#define SCL_PIN = D1
#define SDA_PIN = D2
#define ONE_WIRE_BUS D1
#define ONE_WIRE_BUS D2 

void setup()
{
  //Wire.begin(sdaPin, sclPin);
  Wire.begin();
  Serial.begin(9600);
  while (!Serial); // Waiting for Serial Monitor
  Serial.println("\nI2C Scanner");

}

void loop()
{
  byte error, address;
  int nDevices;

  Serial.println("Scanning...");

  nDevices = 0;
  for (address = 1; address < 127; address++)
  {
    // The i2c scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address < 16) {
        Serial.print("0");
      }
      Serial.print(address, HEX);
      Serial.println(" !");

      nDevices++;
    }
    else if (error == 4)
    {
      Serial.print("Unknown error at address 0x");
      if (address < 16) {
        Serial.print("0");
      }
      Serial.println(address, HEX);
    }
  }
  if (nDevices == 0) {
    Serial.println("No I2C devices found\n");
  }
  else {
    Serial.println("Done.\n");
  }

  delay(2000);
}
