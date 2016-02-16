#include <I2Cdev.h>
#include <MPU6050.h>
#include <Wire.h>//添加必须的库文件
#include <SoftwareSerial.h>
#include "mpu.h"

#include <Adafruit_NeoPixel.h>
#define PIN A0
Adafruit_NeoPixel strip = Adafruit_NeoPixel(6, PIN, NEO_GRB + NEO_KHZ800);

#include "ble.h"

//unsigned long safe_ms = millis();

void setup() {
  Wire.begin();
  Serial.begin(115200);
  mySerial2.begin(9600);
  accelgyro.initialize();
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  ble();
  if (!color_en)
  {
    getMPU();
    colorWipe(strip.Color(Angel_accX, Angel_accY, Angel_accZ));
  }
}


