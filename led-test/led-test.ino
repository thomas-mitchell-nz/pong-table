#include <Adafruit_NeoPixel.h>
#define LED_PIN 5
#define LED_COUNT 30

Adafruit_NeoPixel strip(LED_COUNT, 5, NEO_GRB + NEO_KHZ800);

Adafruit_NeoPixel strip2(LED_COUNT, 6, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin(); //always needed
  strip.show(); // 0 data => off.
  strip.setBrightness(250); // ~20% (max = 255)

  strip2.begin(); //always needed
  strip2.show(); // 0 data => off.
  strip2.setBrightness(250); // ~20% (max = 255)
  Serial.begin(9600); 
}

void loop() {
  int n = strip.numPixels();
  // fph = FirstPixelHue
  
  for (long fph = 0; fph < 5 * 65536; fph += 256) {
    for (int i = 0; i < n; i++) {
      int pixelHue = fph + (i * 65536L / n);
      strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
      strip2.setPixelColor(i, strip2.gamma32(strip2.ColorHSV(pixelHue)));
    }
    strip.show();
    strip2.show();
    delay(10);
  }
  strip.show();
  strip2.show();
  delay(100);
}
