/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "application.h"
#line 1 "/home/ryan/projects/i2cscanner/src/i2cscanner.ino"
#include <Wire.h>
#include <TCA9548A-RK.h>

void setup();
void loop();
#line 4 "/home/ryan/projects/i2cscanner/src/i2cscanner.ino"
SYSTEM_THREAD(ENABLED);
SYSTEM_MODE(SEMI_AUTOMATIC);

TCA9548A mux(Wire, 0);

void setup() {
  Wire.begin();
  Serial.begin(115200);
  Serial.println("\nI2C Scanner");
  mux.begin();
}
 
void loop() {
  byte error, address;
  uint8_t bus;
  int nDevices;
  for(bus = 0; bus < 8; bus++) {
    mux.setChannel(bus);
    Serial.println("Scanning bus " + String(bus) + "...");
    nDevices = 0;
    for(address = 1; address < 127; address++ ) {
      Wire.beginTransmission(address);
      error = Wire.endTransmission();
      if (error == 0) {
        Serial.print("I2C device found at address 0x");
        if (address<16) {
          Serial.print("0");
        }
        Serial.println(address,HEX);
        nDevices++;
      }
      else if (error==4) {
        Serial.print("Unknown error at address 0x");
        if (address<16) {
          Serial.print("0");
        }
        Serial.println(address,HEX);
      }    
    }
  }

  if (nDevices == 0) {
    Serial.println("No I2C devices found\n");
  }
  else {
    Serial.println("done\n");
  }
  delay(5000);          
}