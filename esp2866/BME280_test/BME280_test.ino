#include "PubSubClient.h"
#include <ESP8266WiFi.h>
//#include <WiFi.h>
#include <Adafruit_BME280.h>

// define for BME280 sensor
#define SEALEVELPRESSURE_HPA (1013.25)

// use I2C protocol
Adafruit_BME280 bme;

// WiFi prefs
const char* ssid = "ssid";
const char* wifi_password = "pass";

// MQTT prefs
const char* mqtt_server = "192.168.1.10";       // MQTT broker IP (RPI 4 in this case)

const char* temperature_topic = "home/area/BME_temp";
const char* humidity_topic = "home/area/BME_hum";
// more topics

const char* mqtt_username = "user";
const char* mqtt_password = "pass";
const char* clientID = "client_area";

// initialize wifi and mqtt objects
WiFiClient wifiClient;
// 1883 is listener port
PubSubClient client(mqtt_server, 1883, wifiClient);

// function to connect to mqtt broker via wifi
void connect_MQTT() {
  Serial.print("Connecting to: ");  
  Serial.println(ssid);
  WiFi.begin(ssid, wifi_password);
  
  // wait for connection confirmation before continuing
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    
  // for debugging purposes, print IP of ESP8266 module
  Serial.println("WiFi Connected!");
  Serial.print("IP Addr of ESP2866 module: ");
  Serial.println(WiFi.localIP());
  
  // connect to MQTT broker
  if (client.connect(clientID, mqtt_username, mqtt_password)) {
      Serial.println("**** Connected to MQTT Broker ****");
  }
  
  else {
    Serial.println("Connection failed !!!");    
  }
}

void setup() {
  Serial.begin(9600);
  // hardware address defined here
  if (!bme.begin(0x77)) {
    Serial.println("Could not find a valid BME280 sensor, check wiring or default address!");
    while (1);  
  }
}

// print our values
void loop() {
  connect_MQTT();
  Serial.setTimeout(2000);

  float temp = bme.readTemperature() * 9/5 + 32;
  float hum = bme.readHumidity();

  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.println(" *F");
  Serial.print("Humidity: ");
  Serial.print(hum);
  Serial.println(" %");

  // transmit vals as strings
  String tempStr = "Temp: " + String((float)temp) + " F ";
  String humStr = "Hum: " + String((float)hum) + " % ";

  // publish to MQTT broker using previously defined topics
  if (client.publish(temperature_topic, String(temp).c_str())) {
    Serial.println("Temperature sent!");  
  }
  // if msg fails try again
  else {
    Serial.println("Temperature failed to send. Reconnecting to Broker for retry.");
    client.connect(clientID, mqtt_username, mqtt_password);
    delay(10);  // delay ensures client.publish wont interfere with client.connect call
    client.publish(temperature_topic, String(temp).c_str());
  }

  // publish humidity topic
  if (client.publish(humidity_topic, String(hum).c_str())) {
    Serial.println("Humidity sent!");  
  }
  // try again if failed
  else {
    Serial.println("Humidity failed to send. Reconnecting to Broker for retry.");
    client.connect(clientID, mqtt_username, mqtt_password);
    delay(10);  
    client.publish(humidity_topic, String(hum).c_str());
  }
  
  //client.disconnect();
  delay(1000 * 15); // print new vals every 15 seconds  
/*  
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
*/

}
