#include <Arduino.h>

#include <Wire.h>
#include <Arduino_APDS9960.h>
#include <PluggableUSBHID.h>
#include <USBKeyboard.h>

USBKeyboard Keyboard;
// SparkFun_APDS9960 apds = SparkFun_APDS9960();
// sda - 4 scl - rp5
MbedI2C myi2c(p4, p5);
APDS9960 apds(myi2c, 6);
void setup()
{

  myi2c.begin();
  Serial.begin(9600);

  myi2c.setClock(400000);

  delay(3000);

  apds.begin();

  apds.setGestureSensitivity(80);
Serial.println("start");
  delay(1000);
}

void loop()
{
  if (apds.gestureAvailable())
  {
    // a gesture was detected, read and print to Serial Monitor
    int gesture = apds.readGesture();

    switch (gesture)
    {
    case GESTURE_UP:
      Serial.println("Detected UP gesture");
      break;

    case GESTURE_DOWN:
      Serial.println("Detected DOWN gesture");
      break;

    case GESTURE_LEFT:
      Serial.println("Detected LEFT gesture");
      Keyboard.key_code(LEFT_ARROW);
      ;
      break;

    case GESTURE_RIGHT:
      Serial.println("Detected RIGHT gesture");
      Keyboard.key_code(RIGHT_ARROW);
      break;

    default:
      // ignore
      break;
    }
  }
  // Wait 1 second before next reading
  delay(100);
}