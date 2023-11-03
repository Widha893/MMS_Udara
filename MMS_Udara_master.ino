#include "GPS.h"
#include "CJMCU6814.h"
#include "DustSensor.h"
#include "CarbonMonoxideSensor.h"
#include "HydrogenSulfide.h"
#include "ozoneSensor.h"
#include "Sensors.h"
#include "JSON.h"
#include "DataSerialization.h"
#include <PubSubClient.h>
#include <WiFi.h>

const long publishInterval = 2000;

const char* ssid = "Yahaha";
const char* password = "yangituloh";
const char* mqtt_broker = "193.203.160.173";
const char* mqtt_username = "widha893";
const char* mqtt_pass = "Widha123080903";
const char* mqtt_topic = "/sipuber/data";
const int mqtt_port = 1883;
String message = "Test";

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
      if(client.connect("/sipuber/data")){
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
  sensorInit();
  client.setServer(mqtt_broker,mqtt_port);
}

//void loop() {
//  sensorUpdate();
//  if(!client.connected()){
//    reconnect();
//  }
//  nodeUpdate();
//  client.publish("/sipuber/data",json.c_str()); 
//}
void loop() {
  sensorUpdate();
  unsigned long currentTime = millis();

  if (!client.connected()) {
    reconnect();
  }

  if (currentTime - lastPublishTime >= publishInterval) {
    lastPublishTime = currentTime;
    nodeUpdate();
    client.publish("/sipuber/data", json.c_str());
  }
}
