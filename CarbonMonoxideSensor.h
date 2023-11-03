#pragma once
#define carbonPin 32

long RL_carbon = 20000; // disesuaikan dengan resistor sensor
long Ro_carbon = 830; // disesuaikan dengan nilai Rs/Ro sensor

struct{
  float carbon_ADC;
  float carbon_VRL;
  float carbon_Rs;
  float carbon_ppm;
}MQ7;

void updateCarbon(){
  MQ7.carbon_ADC = analogRead(carbonPin);
  MQ7.carbon_VRL = MQ7.carbon_ADC*5.0/4096.0;
  MQ7.carbon_Rs = ( 5.0 * RL_carbon / MQ7.carbon_VRL ) - MQ7.carbon_VRL;
  MQ7.carbon_ppm = 100 * pow(MQ7.carbon_Rs / Ro_carbon,-1.53);
}
