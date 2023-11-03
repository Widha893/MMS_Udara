#pragma once
#include "GPS.h"
#include "CJMCU6814.h"
#include "DustSensor.h"
#include "CarbonMonoxideSensor.h"
#include "HydrogenSulfide.h"
#include "ozoneSensor.h"

void sensorInit(){
  dustSensorInit();
  gpsInit();
//  CJMCUInit();
}

void sensorUpdate(){
  updateDustDensity();
  updateGPS();
//  NO2_update();
  updateCarbon();
  updateHydroSulfide();
  updateOzone();
}
