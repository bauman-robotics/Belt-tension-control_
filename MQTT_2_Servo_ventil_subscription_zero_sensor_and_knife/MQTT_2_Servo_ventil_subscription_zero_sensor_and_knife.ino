#include <ESP8266WiFi.h>
#include <Ticker.h>
#include <AsyncMqttClient.h>
#include <string.h>

#define WIFI_SSID "Bauman_Robotics"
#define WIFI_PASSWORD "31415926"

#define MQTT_HOST IPAddress(94, 228, 120, 144)
#define MQTT_PORT 1883
const char ventil_1_pin = 0;
const char ventil_2_pin = 2;  // + Led_pin
uint8_t mqtt_connected = 0;
int led_num = 0; 

const char topic_wacuum[] = "esp32/leds";
const char topic_knife[] = "esp32/knife";
char servo_knife_pozition = 0;

char knife_up_pozition = 0;
char knife_down_pozition = 90;
const char cmd_knife[] ="knf";

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
  uint16_t packetIdSub = mqttClient.subscribe(topic_wacuum, 2);
  uint16_t packetIdSub_1 = mqttClient.subscribe(topic_knife, 2);
  //Serial.print("Subscribing at QoS 2, packetId: ");
  //Serial.println(packetIdSub);
  //Serial.print("Subscribing at QoS 2, packetId: ");
  //Serial.println(packetIdSub_1);
  //mqttClient.publish("test/lol", 0, true, "test 1");
  //Serial.println("Publishing at QoS 0");
  //uint16_t packetIdPub1 = mqttClient.publish("test/lol", 1, true, "test 2");
  //Serial.print("Publishing at QoS 1, packetId: ");
  //Serial.println(packetIdPub1);
  //uint16_t packetIdPub2 = mqttClient.publish("test/lol", 2, true, "test 3");
  //Serial.print("Publishing at QoS 2, packetId: ");
  //Serial.println(packetIdPub2);
  //led_state = 0;
  //digitalWrite(led_pin,led_state); // Led on
  
  //val_to_send_char = 0; // On, On
  //val_to_send = 0; // On, On
  //val_to_send_str = String(val_to_send);
  //mqttClient.publish("esp32/leds", 0, true, val_to_send_char);
  mqtt_connected = 1;
  Serial.print(cmd_knife);
  Serial.println(knife_up_pozition, DEC);   // set up pozition 
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
  String messageTemp;
  String messageTemp1;
  for (int i = 0; i < len; i++) {
  //Serial.print((char)payload[i]);  
  messageTemp += (char)payload[i];
 }
 //Serial.println();
 if (strcmp (topic, topic_wacuum) == 0) {
  led_num = messageTemp.toInt(); 
  //Serial.print("led_num: ");
  //Serial.println(led_num);
	} 
 else if (strcmp (topic, topic_knife) == 0) {
  messageTemp1 = cmd_knife;
  for (int i = 0; i < len; i++) {
  messageTemp1 += (char)payload[i];
  }
  Serial.println(messageTemp1.c_str());
 }
 //Serial.println();
 // led_num = payload.toInt(); 
 // Serial.println();
}

void onMqttPublish(uint16_t packetId) {
  //Serial.println("Publish acknowledged.");
  //Serial.print("  packetId: ");
  //Serial.println(packetId);
}

void setup() {
  pinMode(ventil_1_pin, OUTPUT);
  pinMode(ventil_2_pin, OUTPUT);
  Serial.begin(115200);
  Serial.println();
  Serial.println();

  wifiConnectHandler = WiFi.onStationModeGotIP(onWifiConnect);
  wifiDisconnectHandler = WiFi.onStationModeDisconnected(onWifiDisconnect);

  mqttClient.onConnect(onMqttConnect);
  //mqttClient.onDisconnect(onMqttDisconnect);
  mqttClient.onSubscribe(onMqttSubscribe);
  //mqttClient.onUnsubscribe(onMqttUnsubscribe);
  mqttClient.onMessage(onMqttMessage);
  //mqttClient.onPublish(onMqttPublish);
  mqttClient.setServer(MQTT_HOST, MQTT_PORT);

  connectToWifi();

  //zero_sensor_old = digitalRead(zero_sensor_pin);
  //pin_2_old = digitalRead(ventil_2_pin);
  //digitalWrite(led_pin,led_state); // Led off
}

void loop() {
 if (mqtt_connected) {
  if (led_num & 1) digitalWrite(ventil_1_pin, HIGH);
    else digitalWrite(ventil_1_pin, LOW);
  if (led_num & 2) digitalWrite(ventil_2_pin, HIGH);
    else digitalWrite(ventil_2_pin, LOW);
  }
}
