#include "Kalman_filter.h"
#define PM10_READ A4
#define PM10_LED  23

// PM10 Sensor
int samplingTime      = 280;
int deltaTime         = 40; 
int sleepTime         = 9680;
float voMeasured      = 0.0;
float calcVoltage     = 0.0;
float dustDensity     = 0.0;
float dustDensity_ppm = 0.0;

void dustSensorRead()
{
  digitalWrite(PM10_LED,LOW); // power on the LED
  delayMicroseconds(samplingTime);
  voMeasured = analogRead(PM10_READ); // read the dust value
  delayMicroseconds(deltaTime);
  digitalWrite(PM10_LED,HIGH); // turn the LED off
  delayMicroseconds(sleepTime);
  calcVoltage = voMeasured * (5.0 / 1024.0);
  dustDensity = 170 * calcVoltage - 0.1;
}

void updateDustDensity()
{
  dustSensorRead();
  kalman_filter(dustDensity);
  dustDensity_ppm = kalman_data/1000.0f;
}
