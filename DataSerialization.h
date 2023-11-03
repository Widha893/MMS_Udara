#pragma once
#include "JSON.h"
#include "DustSensor.h"
#include "GPS.h"
//
//StaticJsonDocument<300> json_data;
//String newstr;
//String serializedData;
//
//void nodeUpdate()
//{
///*JSON*/
//    json_data["dust"] = dustDensity_ppm;
//
//    String messg;
//    serializeJson(json_data, serializedData);
//    // messg += '@';
//    // Serial.println(messg);
//}

String json;
void nodeUpdate(){
  json = "{";
  json += "";
  json += "dust";
  json += "";
  json += ":";
  json += String(dustDensity_ppm);
  json += "";
  json += ",";
  json += "";
  json += "latitude";
  json += "";
  json += ":";
  json += "";
  json += String(GPS_data.latitude,7);
  json += "";
  json += ",";
  json += "";
  json += "longitude";
  json += "";
  json += ":";
  json += "";
  json += String(GPS_data.longitude,7);
  json += "";
  json += ",";
  json += "";
  json += "NO2";
  json += "";
  json += ":";
  json += "";
  json += "0";
  json += "";
  json += ",";
  json += "";
  json += "CO";
  json += "";
  json += ":";
  json += "";
  json += String(MQ7.carbon_ppm);
  json += "";
  json += ",";
  json += "";
  json += "H2S";
  json += "";
  json += ":";
  json += "";
  json += String(MQ136.hydroSulfide_ppm);
  json += "";
  json += ",";
  json += "";
  json += "Ozone";
  json += "";
  json += ":";
  json += "";
  json += String(MQ131.ozone_ppm);
  json += "";
  json += "}";  
}
