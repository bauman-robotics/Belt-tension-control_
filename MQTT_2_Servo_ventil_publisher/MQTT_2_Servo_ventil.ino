//https://github.com/plapointe6/EspMQTTClient/blob/master/examples/SimpleMQTTClient/SimpleMQTTClient.ino
/*
  SimpleMQTTClient.ino
  The purpose of this exemple is to illustrate a simple handling of MQTT and Wifi connection.
  Once it connects successfully to a Wifi network and a MQTT broker, it subscribe to a topic and send a message to it.
  It will also send a message delayed 5 seconds later.
*/

#include "EspMQTTClient.h"

//const char led = 2; 
int led_num = 0; 
const char ventil_1_pin = 0;
const char ventil_2_pin = 2;

EspMQTTClient client(
  "Bauman_Robotics",
  "31415926",
  "94.228.120.144",  // MQTT Broker server ip
  "MQTTUsername",   // Can be omitted if not needed
  "MQTTPassword",   // Can be omitted if not needed
  "TestClient",     // Client name that uniquely identify your device
  1883              // The MQTT port, default to 1883. this line can be omitted
);

void setup()
{
  pinMode(ventil_1_pin, OUTPUT);
  pinMode(ventil_2_pin, OUTPUT);
  Serial.begin(115200);

  // Optional functionalities of EspMQTTClient
  client.enableDebuggingMessages(); // Enable debugging messages sent to serial output
  client.enableHTTPWebUpdater(); // Enable the web updater. User and password default to values of MQTTUsername and MQTTPassword. These can be overridded with enableHTTPWebUpdater("user", "password").
  client.enableOTA(); // Enable OTA (Over The Air) updates. Password defaults to MQTTPassword. Port is the default OTA port. Can be overridden with enableOTA("password", port).
  client.enableLastWillMessage("TestClient/lastwill", "I am going offline");  // You can activate the retain flag by setting the third parameter to true

  //digitalWrite(ventil_1_pin, LOW);
  //digitalWrite(ventil_2_pin, LOW);
}

// This function is called once everything is connected (Wifi and MQTT)
// WARNING : YOU MUST IMPLEMENT IT IF YOU USE EspMQTTClient
void onConnectionEstablished()
{
  // Subscribe to "esp32/leds" and display received message to Serial
  client.subscribe("esp32/leds", [](const String & payload) {
  led_num = payload.toInt(); 
  Serial.println();
  });

  // Publish a message to "mytopic/test"
  // client.publish("mytopic/test", "This is a message"); // You can activate the retain flag by setting the third parameter to true

  // Execute delayed instructions
  // client.executeDelayed(5 * 1000, []() {
  //   client.publish("mytopic/wildcardtest/test123", "This is a message sent 5 seconds later");  
}

void loop()
{
  client.loop();
  if (led_num & 1) digitalWrite(ventil_1_pin, HIGH);
    else digitalWrite(ventil_1_pin, LOW);
  if (led_num & 2) digitalWrite(ventil_2_pin, HIGH);
    else digitalWrite(ventil_2_pin, LOW);
}
