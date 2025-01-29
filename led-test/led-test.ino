/* 
 * Filename: led-test.ino
 * FileType: Arduino source file
 * Author: Thomas Mitchell
 * Last modified: 31/7/2023
 * Description: Test script for leds
 */

#include <Adafruit_NeoPixel.h>
#define LED_COUNT 30

Adafruit_NeoPixel strip1(LED_COUNT, 5, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2(LED_COUNT, 6, NEO_GRB + NEO_KHZ800);

void setup() {
  strip1.begin();
  strip2.begin();
  strip1.show();
  strip2.show();
  strip1.setBrightness(250);
  strip2.setBrightness(250);
}

void loop() {
 int n = strip1.numPixels();
  for (long fph = 0; fph < 5 * 65536; fph += 256) {  // fph = FirstPixelHue
    for (int i = 0; i < n; i++) {
      int pixelHue = fph + (i * 65536L / n);
      strip1.setPixelColor(i, strip1.gamma32(strip1.ColorHSV(pixelHue)));
      strip2.setPixelColor(i, strip2.gamma32(strip2.ColorHSV(pixelHue)));
    }
    strip1.show();
    strip2.show();
    delay(10);
  }
}
