#include "arduino.h"
SoftwareSerial mySerial(4, 5);

#define mySerial2 Serial1 // RX, TX   //ble

String currentInfo;
char buffer[100];
int sensorValue = 0;
boolean buffer_sta = false;
int buffer_num = 0;
int sta[4];
boolean color_en;
long ble_safe_ms = millis();
#define PIXEL_COUNT  6

void colorWipe(uint32_t c) {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
  }
}
void colorWipe(uint32_t c, int i) {
  strip.setPixelColor(i, c);
  strip.show();
}

void ble()
{
  while (mySerial2.available())
  {
    char c = mySerial2.read();
    delay(2);

    if (c == 'C')
      buffer_sta = true;
    if (c == '\n')
    {
      color_en = true;
      ble_safe_ms = millis();
    }
    if (buffer_sta)
    {
      buffer[buffer_num] = c;
      buffer_num++;
    }
    //  Serial.println(c);
    //Serial.println(color_en);
  }

  if (buffer_sta)
  {
    buffer_sta = false;

    sscanf((char *)strstr((char *)buffer, "C:"), "C:%d,%d,%d,%d", &sta[0], &sta[1], &sta[2], &sta[3]);

    for (int a = 0; a < buffer_num; a++)
      buffer[a] = NULL;
    buffer_num = 0;

    for (int i = 0; i < 4; i++)
    {
      Serial.print(sta[i]);
      Serial.print(",");
    }
    Serial.println(" ");

    if (-1 == sta[3]) {
      colorWipe(strip.Color(sta[0], sta[1], sta[2]));
    }
    else if ((0 <= sta[3]) && (sta[3] < PIXEL_COUNT)) {
      colorWipe(strip.Color(sta[0], sta[1], sta[2]), sta[3]);
    }
  }

  if (millis() - ble_safe_ms > 2000)
  {
    ble_safe_ms = millis();
    color_en = false;
  }
}
