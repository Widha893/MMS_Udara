#include <math.h>
#define NH3PIN   35
#define COPIN    34
#define OXPIN    32

// CJMCU Sensor
uint16_t NH3baseR;
uint16_t REDbaseR;
uint16_t OXbaseR;

enum channel {
  CH_NH3, CH_RED, CH_OX
};
typedef enum channel channel_t;

enum gas {
  CO, NO2, NH3
};
typedef enum gas gas_t;

uint16_t getResistance(channel_t channel) {
      unsigned long rs = 0;
      int counter = 0;

  switch (channel) {
    case CH_NH3:
      for(int i = 0; i < 100; i++) {
        rs += analogRead(NH3PIN);
        counter++;
        delay(2);
      }
      return rs/counter;
    case CH_RED:
      for(int i = 0; i < 100; i++) {
        rs += analogRead(COPIN);
        counter++;
        delay(2);
      }
      return rs/counter;
    case CH_OX:      
      for(int i = 0; i < 100; i++) {
        rs += analogRead(OXPIN);
        counter++;
        delay(2);
      }
      return rs/counter;
  }
}

void calibrateCJMCU() {
  uint8_t seconds = 10;
  uint8_t delta = 2;

  uint16_t bufferNH3[seconds];
  uint16_t bufferRED[seconds];
  uint16_t bufferOX[seconds];

  uint8_t pntrNH3 = 0;
  uint8_t pntrRED = 0;
  uint8_t pntrOX = 0;

  uint16_t fltSumNH3 = 0;
  uint16_t fltSumRED = 0;
  uint16_t fltSumOX = 0;

  uint16_t curNH3;
  uint16_t curRED;
  uint16_t curOX;

  bool NH3stable = false;
  bool REDstable = false;
  bool OXstable = false;

  for (int i = 0; i < seconds; ++i) {
    bufferNH3[i] = 0;
    bufferRED[i] = 0;
    bufferOX[i] = 0;
  }

  do {
    // Wait a second
    delay(1000);
    Serial.print(".");
    // Read new resistances
    unsigned long rs = 0;
    delay(50);
    for (int i = 0; i < 3; i++) {
    delay(1);
    rs += analogRead(NH3PIN);
    }
    curNH3 = rs/3;
    rs = 0;
    delay(50);
    for (int i = 0; i < 3; i++) {
    delay(1);
    rs += analogRead(COPIN);
    }
    curRED = rs/3;
    rs = 0;
    delay(50);
    for (int i = 0; i < 3; i++) {
    delay(1);
    rs += analogRead(OXPIN);
    }
    curOX = rs/3;

    fltSumNH3 = fltSumNH3 + curNH3 - bufferNH3[pntrNH3];
    fltSumRED = fltSumRED + curRED - bufferRED[pntrRED];
    fltSumOX = fltSumOX + curOX - bufferOX[pntrOX];

    bufferNH3[pntrNH3] = curNH3;
    bufferRED[pntrRED] = curRED;
    bufferOX[pntrOX] = curOX;

    NH3stable = abs(fltSumNH3 / seconds - curNH3) < delta;
    REDstable = abs(fltSumRED / seconds - curRED) < delta;
    OXstable = abs(fltSumOX / seconds - curOX) < delta;

    pntrNH3 = (pntrNH3 + 1) % seconds ;
    pntrRED = (pntrRED + 1) % seconds;
    pntrOX = (pntrOX + 1) % seconds;

    if(!NH3stable) {
      Serial.print("(NH3:");
      Serial.print(abs(fltSumNH3 / seconds - curNH3));
      Serial.print(")");
    }
    if(!REDstable) {
      Serial.print("(RED:");
      Serial.print(abs(fltSumNH3 / seconds - curRED));
      Serial.print(")");
    }
    if(!OXstable) {
      Serial.print("(OX:");
      Serial.print(abs(fltSumNH3 / seconds - curOX));
      Serial.print(")");
    }

  } while (!NH3stable || !REDstable || !OXstable);

  NH3baseR = fltSumNH3 / seconds;
  REDbaseR = fltSumRED / seconds;
  OXbaseR = fltSumOX / seconds;
}

uint16_t getBaseResistance(channel_t channel) {
  switch (channel) {
    case CH_NH3:
      return NH3baseR;
    case CH_RED:
      return REDbaseR;
    case CH_OX:
      return OXbaseR;
  }  
}

float getCurrentRatio(channel_t channel) {
  float baseResistance = (float) getBaseResistance(channel);
  float resistance = (float) getResistance(channel);
  return resistance / baseResistance * (4095.0 - baseResistance) / (4095.0 - resistance);
  return -1.0;
}

float measureCJMCU(gas_t gas) {
  float ratio;
  float c = 0;

  switch (gas) {
    case CO:
      ratio = getCurrentRatio(CH_RED);
      c = pow(ratio, -1.179) * 4.385;
      break;
    case NO2:
      ratio = getCurrentRatio(CH_OX);
      c = pow(ratio, 1.007) / 6.855;
      break;
    case NH3:
      ratio = getCurrentRatio(CH_NH3);
      c = pow(ratio, -1.67) / 1.47;
      break;
  }

  return isnan(c) ? -1 : c;
}
