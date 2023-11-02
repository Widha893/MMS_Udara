#include "GPS.h"
#include "CJMCU6814.h"
#include "DustSensor.h"
#include "JSON.h"
#include "DataSerialization.h"
#include <PubSubClient.h>
#include <WiFi.h>

long timelast,timenow,dt;

const char* ssid = "Yahaha";
const char* password = "yangituloh";
const char* mqtt_broker = "broker.hivemq.com";
const char* mqtt_username = "widha893";
const char* mqtt_pass = "Widha123080903";
const char* mqtt_topic = "sipuber/data";
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
      if(client.connect("/sipuber/dataTest")){
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
  dustSensorInit();
  gpsInit();
  CJMCUInit();
  client.setServer(mqtt_broker,mqtt_port);
}

void loop() {
  updateDustDensity();
  updateGPS();
  NO2_update();
  if(!client.connected()){
    reconnect();
  }
  nodeUpdate();
//  serializedData = "test";
  client.publish("/sipuber/dataTest",json.c_str()); 
//  }
}
