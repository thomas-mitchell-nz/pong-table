#include <Adafruit_NeoPixel.h>
#define LED_PIN 2
#define LED_COUNT 30
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
 strip.begin(); //always needed
 strip.show(); // 0 data => off.
 strip.setBrightness(50); // ~20% (max = 255)
}

void loop() {
 int n = strip.numPixels();
 // fph = FirstPixelHue
  for (long fph = 0; fph < 5 * 65536; fph += 256) {
    for (int i = 0; i < n; i++) {
      int pixelHue = fph + (i * 65536L / n);
      strip.setPixelColor(i,strip.gamma32(strip.ColorHSV(pixelHue)));
    }
    strip.show();
    delay(10);
  }
}
