#pragma once
#define hydroSulfidePin 35

long RL_hydroSulfide = 20000; // disesuaikan dengan resistor sensor
long Ro_hydroSulfide = 104.611; // disesuaikan dengan nilai Rs/Ro sensor

struct{
  float hydroSulfide_ADC;
  float hydroSulfide_VRL;
  float hydroSulfide_Rs;
  float hydroSulfide_ppm;
}MQ136;

void updateHydroSulfide(){
  MQ136.hydroSulfide_ADC = analogRead(hydroSulfidePin);
  MQ136.hydroSulfide_VRL = MQ136.hydroSulfide_ADC*5.0/4096.0;
  MQ136.hydroSulfide_Rs = ( 5.0 * RL_hydroSulfide / MQ136.hydroSulfide_VRL ) - MQ136.hydroSulfide_VRL;
  MQ136.hydroSulfide_ppm = 39.996 * pow(MQ136.hydroSulfide_Rs / Ro_hydroSulfide,-3.303);
}
