#include <OneWire.h>
#include <DallasTemperature.h>

#include <ESP8266WiFi.h>

#include <Ticker.h>
#include <AsyncMqttClient.h>

//#include <Adafruit_SSD1306.h>

#define OLED_RESET 0
//Adafruit_SSD1306 display(OLED_RESET);

// WiFi prefs
const char* ssid = "ssid";
const char* wifi_password = "pass";

// RPI IP address (MQTT Broker)
#define MQTT_HOST IPAddress(192, 168, 1, 10)
// #define MQTT_HOST IPAddress(192, 168, 1, 134)
#define MQTT_PORT 1883
#define MQTT_TOPIC_TEMP "ds18b20/Temperature"

OneWire ds(D6);
DallasTemperature sensors(&ds);

float temperature;

AsyncMqttClient mqttClient;
Ticker mqttReconnectTimer;

void connectToMqtt() {
  Serial.println("Connecting to MQTT...");
  mqttClient.connect();
}

void onMqttConnect(bool sessionPresent) {
  Serial.println("Connected to MQTT");
  Serial.print("Session present: ");
  Serial.println(sessionPresent);
}

void onMqttDisconnect(AsyncMqttClientDisconnectReason reason) {
  Serial.println("Disconnected from MQTT");

  if (WiFi.isConnected()) {
    mqttReconnectTimer.once(2, connectToMqtt);
  }
}

void onMqttPublish(uint16_t packetId) {
  Serial.print("Publish acknowledged.");
  Serial.print("  packetId: ");
  Serial.println(packetId);
}

void setup() {
  Serial.begin(115200);

  // Lets fuck with the OLED Shield now...
  /*
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  delay(2000);
  display.clearDisplay();
  display.drawPixel(10, 10, WHITE);
  display.display();
  delay(2000);
  display.clearDisplay();
  */

  WiFi.begin(WIFI_SSID, WIFI_PASS);

  Serial.print("Connecting to: ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }

  Serial.println();
  Serial.print("Connected: IP Address: ");
  Serial.println(WiFi.localIP());

  mqttClient.onConnect(onMqttConnect);
  mqttClient.onDisconnect(onMqttDisconnect);
  mqttClient.onPublish(onMqttPublish);
  mqttClient.setServer(MQTT_HOST, MQTT_PORT);
  connectToMqtt();
}

void loop() {
  sensors.requestTemperatures();
  temperature = sensors.getTempFByIndex(0);
  Serial.println(temperature);

  uint16_t packetIdPub = mqttClient.publish(MQTT_TOPIC_TEMP, 1, true, String(temperature).c_str());

  delay(1000);
}
