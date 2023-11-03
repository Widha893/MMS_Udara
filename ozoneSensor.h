#pragma once
#define ozonePin 33

long RL_ozone = 20000; // disesuaikan dengan resistor sensor
long Ro_ozone = 1917.22; // disesuaikan dengan nilai Rs/Ro sensor

struct{
  float ozone_ADC;
  float ozone_VRL;
  float ozone_Rs;
  float ozone_ppm;
}MQ131;

void updateOzone(){
  MQ131.ozone_ADC = analogRead(ozonePin);
  MQ131.ozone_VRL = MQ131.ozone_ADC*5.0/4096.0;
  MQ131.ozone_Rs = ( 5.0 * RL_ozone / MQ131.ozone_VRL ) - MQ131.ozone_VRL;
  MQ131.ozone_ppm = 100 * pow(MQ131.ozone_Rs / Ro_ozone,-1.53);
}
