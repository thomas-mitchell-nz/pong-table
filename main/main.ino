#include <Adafruit_NeoPixel.h>
#include "Arduino.h"
#include "Cup.h"

#define LED_COUNT 30
#define NUM_CUPS 10

Adafruit_NeoPixel strip1(LED_COUNT, 2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2(LED_COUNT, 6, NEO_GRB + NEO_KHZ800);

Cup side1[NUM_CUPS] = {
  Cup(&strip1, 0, 1, 11, 23, A1),
  Cup(&strip1, 2, 3, 10, 25, A2),
  Cup(&strip1, 4, 5, 9, 27, A5),
  Cup(&strip1, 6, 7, 8, 29, A6),
  Cup(&strip1, 12, 13, 20, 35, A9),
  Cup(&strip1, 14, 15, 19, 33, A8),
  Cup(&strip1, 16, 17, 18, 31, A7),
  Cup(&strip1, 23, 24, 25, 39, A11),
  Cup(&strip1, 21, 22, 26, 37, A10),
  Cup(&strip1, 27, 28, 29, 41, A12)
};

Cup side2[NUM_CUPS] = {
  //Cup(&strip, 0, 1, 11, 43, A13),
  //Cup(&strip, 2, 3, 10, 45, A14),
  //Cup(&strip, 4, 5, 9, 47, A15),
  //Cup(&strip, 6, 7, 8, 11, A3, true, 0),
  //Cup(&strip, 12, 13, 20, 12, A0, true, 1),
  //Cup(&strip, 14, 15, 19, 13, A0, true, 2),
  //Cup(&strip, 16, 17, 18, 10, A0, true, 3),
  //Cup(&strip, 23, 24, 25, 53, A0, true, 4),
  //Cup(&strip, 21, 22, 26, 49, A0, true, 5),
  //Cup(&strip, 27, 28, 29, 51, A0, true, 6)
};

void setup() 
{
  strip1.begin(); //always needed
  strip1.show(); // 0 data => off.
  strip1.setBrightness(250); // ~20% (max = 255)
  
  strip2.begin();
  strip2.show();
  strip2.setBrightness(250);
  
  Serial.begin(9600); 
  
  for (int i =0; i < NUM_CUPS; i++) {
    side1[i].calibrate();
    side2[i].calibrate();
  }

  side1[9].printSignal = true;
}

void loop() 
{
  strip1.show();
  
  int n = strip1.numPixels();
  fph = FirstPixelHue
  
  for (long fph = 0; fph < 5 * 65536; fph += 256) {
    for (int i = 0; i < n; i++) {
      int pixelHue = fph + (i * 65536L / n);
      strip1.setPixelColor(i, strip1.gamma32(strip1.ColorHSV(pixelHue)));
      strip2.setPixelColor(i, strip2.gamma32(strip2.ColorHSV(pixelHue)));
      for (int j = 0; j < NUM_CUPS; j++) {
        if (side1[j].checkForCup = true) {
          side1[j].turnRed();
        }
        if (side2[j].checkForCup = true) {
          side2[j].turnRed();
        }
      }
    }
    strip1.show();
    strip2.show();
    delay(10);
  }
}
