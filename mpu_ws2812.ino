#include <I2Cdev.h>
#include <MPU6050.h>
#include <Wire.h>//添加必须的库文件
#include "mpu.h"
#include <Adafruit_NeoPixel.h>
#define PIN A0
Adafruit_NeoPixel strip = Adafruit_NeoPixel(6, PIN, NEO_GRB + NEO_KHZ800);

unsigned long safe_ms=millis();

void setup() {
  Wire.begin();
  Serial.begin(115200);
  accelgyro.initialize();

}

void loop() {
    strip.begin();
    strip.show(); // Initialize all pixels to 'off'
    getMPU();
    
    colorWipe(strip.Color(Angel_accX, Angel_accY, Angel_accZ), 10);
    safe_ms=millis();
  }


void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}


