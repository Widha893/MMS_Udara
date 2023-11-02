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
  json += String(GPS_data.latitude,6);
  json += "";
  json += ",";
  json += "";
  json += "longitude";
  json += "";
  json += ":";
  json += "";
  json += String(GPS_data.longitude,6);
  json += "";
  json += ",";
  json += "";
  json += "NO2";
  json += "";
  json += ":";
  json += "";
  json += String(no2.NO2_ppm);
  json += "";
  json += "}";  
}
