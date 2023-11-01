#include "GPS.h"
#include "CJMCU6814.h"
#include "DustSensor.h"
#include "JSON.h"
#include <PubSubClient.h>
#include <WiFi.h>

const char* ssid = "Yahaha";
const char* password = "yangituloh";
const char* mqtt_broker = "193.203.160.173";
const char* mqtt_username = "widha893";
const char* mqtt_pass = "Widha123080903";
const int mqtt_port = 1883;

WiFiClient espclient;
PubSubClient client(espclient);

void setupWifi(){
  delay(100);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED){
    delay(100);
    Serial.print("=");
  }
  Serial.println();
  Serial.print("Connected to ");
  Serial.println(ssid);
}

void reconnect(){
  while(!client.connected()){
    Serial.print("\nConnected to");
    Serial.println(mqtt_broker);
      if(client.connect("MQTT_Topic")){
        Serial.print("\nConnected to");
        Serial.println(mqtt_broker);
      }else{
        Serial.println("\nTrying connect again");
        delay(5000);
      }
  }
}

void setup() {
  Serial.begin(115200);
  setupWifi();
  client.setServer(mqtt_broker,mqtt_port);
}

void loop() {
  // put your main code here, to run repeatedly:

}
