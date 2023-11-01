#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>
#define GPS_RX 4
#define GPS_TX 3

static const int GPS_baudrate = 9600;

// Objects
TinyGPSPlus gps;
SoftwareSerial _gps_(GPS_RX, GPS_TX);

struct{
  double latitude;
  double longitude;
}GPS_data;

void gpsSetup(){
  _gps_.begin(GPS_baudrate);
  Serial.println("GPS setup complete!");
}

void getGPSLocation()
{
  if (gps.location.isValid())
  {
    GPS_data.latitude = gps.location.lat();
    GPS_data.longitude = gps.location.lng();
  }
  else
  {
    GPS_data.latitude = 0.0;
    GPS_data.longitude = 0.0;
  }
}

void updateGPS()
{
  while(_gps_.available() > 0){
    if(gps.encode(_gps_.read())){
      getGPSLocation();
    }
  }
}
