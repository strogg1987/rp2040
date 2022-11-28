#include <Arduino.h>

#include <Wire.h>
#include <SparkFun_APDS9960.h>
#include <PluggableUSBHID.h>
#include <USBKeyboard.h>
USBKeyboard Keyboard;
SparkFun_APDS9960 apds = SparkFun_APDS9960();
//sda - 4 scl - 5

void setup() {
  Wire.begin();
  Serial.begin(9600);


  Wire.setClock(400000);


  delay(3000);
Keyboard.key_code('R');
Keyboard.key_code('P');
  // Initialize APDS-9960 (configure I2C and initial values)
  if ( apds.init() ) {
    Serial.println(F("APDS-9960 initialization complete"));
  } else {
    Serial.println(F("Something went wrong during APDS-9960 init!"));
  }
  apds.enableGestureSensor(false);
    // Wait for initialization and calibration to finish
  delay(1000);

}


void loop() {

   if ( apds.isGestureAvailable() ) {
    switch ( apds.readGesture() ) {
      case DIR_UP:
        Serial.println("UP");
        break;
      case DIR_DOWN:
        Serial.println("DOWN");
        break;
      case DIR_LEFT:
        Serial.println("LEFT");
        Keyboard.key_code(LEFT_ARROW);
        break;
      case DIR_RIGHT:
        Serial.println("RIGHT");
        Keyboard.key_code(RIGHT_ARROW);
        break;
      case DIR_NEAR:
        Serial.println("NEAR");
        break;
      case DIR_FAR:
        Serial.println("FAR");
        break;
      default:
        Serial.println("NONE");
    }
  }
  // Wait 1 second before next reading
  delay(100);

  
}