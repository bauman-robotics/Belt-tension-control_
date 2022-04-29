#include <ESP8266WiFi.h>
#include <Ticker.h>
#include <AsyncMqttClient.h>

#define WIFI_SSID "Bauman_Robotics"
#define WIFI_PASSWORD "31415926"

#define MQTT_HOST IPAddress(94, 228, 120, 144)
#define MQTT_PORT 1883

//pins
const char ventil_2_pin = 2;    // input // inline led pin
const char zero_sensor_pin = 3; //rx // input
//const char led_pin = 1; // tx   // out -was // at now input kinfe
const char knife_pin = 1; // tx   // out -was // at now input kinfe
const char led_pin = 0; //extern led // prg_pin
//----
uint8_t pin_2_old = 1; // after reset
uint8_t pin_2_now = 1; 
uint8_t change_state_pin_2 = 0; 
char led_state = 1; // off
uint8_t      val_to_send = 0;
String       val_to_send_str = "";
const char * val_to_send_char;
//kinfe
char       knife_up[] = "0";
char       knife_down[] = "85";
uint8_t knife_pin_state_old = 0;
uint8_t knife_pin_state_now = 0;
//--
uint8_t mqtt_connected = 0;


AsyncMqttClient mqttClient;
Ticker mqttReconnectTimer;

WiFiEventHandler wifiConnectHandler;
WiFiEventHandler wifiDisconnectHandler;
Ticker wifiReconnectTimer;

void connectToWifi() {
  //Serial.println("Connecting to Wi-Fi...");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
}

void connectToMqtt() {
  //Serial.println("Connecting to MQTT...");
  mqttClient.connect();
}

void onWifiConnect(const WiFiEventStationModeGotIP& event) {
  //Serial.println("Connected to Wi-Fi.");
  connectToMqtt();
}

void onWifiDisconnect(const WiFiEventStationModeDisconnected& event) {
  //Serial.println("Disconnected from Wi-Fi.");
  mqttReconnectTimer.detach(); // ensure we don't reconnect to MQTT while reconnecting to Wi-Fi
  wifiReconnectTimer.once(2, connectToWifi);
}

void onMqttConnect(bool sessionPresent) {
  //Serial.println("Connected to MQTT.");
  //Serial.print("Session present: ");
  //Serial.println(sessionPresent);
  //uint16_t packetIdSub = mqttClient.subscribe("test/lol", 2);
  //Serial.print("Subscribing at QoS 2, packetId: ");
  //Serial.println(packetIdSub);
  //mqttClient.publish("test/lol", 0, true, "test 1");
  //Serial.println("Publishing at QoS 0");
  //uint16_t packetIdPub1 = mqttClient.publish("test/lol", 1, true, "test 2");
  //Serial.print("Publishing at QoS 1, packetId: ");
  //Serial.println(packetIdPub1);
  //uint16_t packetIdPub2 = mqttClient.publish("test/lol", 2, true, "test 3");
  //Serial.print("Publishing at QoS 2, packetId: ");
  //Serial.println(packetIdPub2);
  led_state = 0;                   // Led on
  digitalWrite(led_pin,led_state); // Led on
  
  //val_to_send_char = 0; // On, On
  //val_to_send = 0; // On, On
  //val_to_send_str = String(val_to_send);
  //mqttClient.publish("esp32/leds", 0, true, val_to_send_char);

  //ventil_ctrl
  val_to_send = 0; // On, On
  val_to_send_str = String(val_to_send);
  val_to_send_char = val_to_send_str.c_str();
  mqttClient.publish("esp32/leds", 0, true, val_to_send_char); // On, On
  //---
  //knife
  mqttClient.publish("esp32/knife", 0, true, knife_up); // 0 degrees 
  //-- 
  mqtt_connected = 1;
}

void onMqttDisconnect(AsyncMqttClientDisconnectReason reason) {
  //Serial.println("Disconnected from MQTT.");
  if (WiFi.isConnected()) {
    mqttReconnectTimer.once(2, connectToMqtt);
  }
  mqtt_connected = 0;
}

void onMqttSubscribe(uint16_t packetId, uint8_t qos) {
  //Serial.println("Subscribe acknowledged.");
  //Serial.print("  packetId: ");
  //Serial.println(packetId);
  //Serial.print("  qos: ");
  //Serial.println(qos);
}

void onMqttUnsubscribe(uint16_t packetId) {
  //Serial.println("Unsubscribe acknowledged.");
  //Serial.print("  packetId: ");
  //Serial.println(packetId);
}

void onMqttMessage(char* topic, char* payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total) {
  //Serial.println("Publish received.");
  //Serial.print("  topic: ");
  //Serial.println(topic);
  //Serial.print("  qos: ");
  //Serial.println(properties.qos);
  //Serial.print("  dup: ");
  //Serial.println(properties.dup);
  //Serial.print("  retain: ");
  //Serial.println(properties.retain);
  //Serial.print("  len: ");
  //Serial.println(len);
  //Serial.print("  index: ");
  //Serial.println(index);
  //Serial.print("  total: ");
  //Serial.println(total);
}

void onMqttPublish(uint16_t packetId) {
  //Serial.println("Publish acknowledged.");
  //Serial.print("  packetId: ");
  //Serial.println(packetId);
}

void setup() {
  pinMode(zero_sensor_pin, INPUT);
  pinMode(ventil_2_pin, INPUT);
  pinMode(knife_pin, INPUT);
  pinMode(led_pin, OUTPUT);
  //Serial.begin(115200);
  //Serial.println();
  //Serial.println();
  //led_state = 1; //off
  //digitalWrite(led_pin,led_state); // Led off

  wifiConnectHandler = WiFi.onStationModeGotIP(onWifiConnect);
  wifiDisconnectHandler = WiFi.onStationModeDisconnected(onWifiDisconnect);

  mqttClient.onConnect(onMqttConnect);
  mqttClient.onDisconnect(onMqttDisconnect);
  mqttClient.onSubscribe(onMqttSubscribe);
  mqttClient.onUnsubscribe(onMqttUnsubscribe);
  mqttClient.onMessage(onMqttMessage);
  mqttClient.onPublish(onMqttPublish);
  mqttClient.setServer(MQTT_HOST, MQTT_PORT);

  connectToWifi();  
  pin_2_old = digitalRead(ventil_2_pin);
}

void loop() {
 if (mqtt_connected) {
  delay(10);  
  // ventil control 
  pin_2_now = digitalRead(ventil_2_pin);  // = 1 after reset
  if (pin_2_now != pin_2_old) {
    change_state_pin_2 = 1; 
    pin_2_old = pin_2_now;
  }
  else change_state_pin_2 = 0;
   if (change_state_pin_2) {
    led_state ^=1;
    digitalWrite(led_pin,led_state); 
     if      ((pin_2_now ==0) && (digitalRead(zero_sensor_pin) == 0)) val_to_send = 2; // P0 = On, P1 = Off;
     else if ((pin_2_now ==0) && (digitalRead(zero_sensor_pin) == 1)) val_to_send = 1; // P0 = Off, P1 = On;
     else if (pin_2_now ==1) val_to_send = 0; // P0 = On, P1 = On;
     change_state_pin_2 = 0; 
     val_to_send_str = String(val_to_send);
     val_to_send_char = val_to_send_str.c_str();
     mqttClient.publish("esp32/leds", 0, true, val_to_send_char);
   }
   //knife control 
   knife_pin_state_now  = digitalRead(knife_pin); 
   if (knife_pin_state_old != knife_pin_state_now) {
      knife_pin_state_old = knife_pin_state_now;
      led_state ^=1;
      digitalWrite(led_pin,led_state); 
    if (knife_pin_state_now) {
      mqttClient.publish("esp32/knife", 0, true, knife_up);
    } else 
      mqttClient.publish("esp32/knife", 0, true, knife_down);
   }   
 }  
}
