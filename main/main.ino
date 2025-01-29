/* 
 * Filename: main.ino
 * FileType: Arduino source file
 * Author: Thomas Mitchell
 * Last modified: 23/8/2023
 * Description: Script for interactive LED beer pong table
 */

#include <Adafruit_NeoPixel.h>
#include <Arduino.h>
#include "Cup.h"

#define LED_COUNT     30
#define NUM_CUPS      10
#define STARTING_CUP  4  
#define SWITCH_PIN    3

Adafruit_NeoPixel strip1(LED_COUNT, 5, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2(LED_COUNT, 6, NEO_GRB + NEO_KHZ800);


Cup side1[NUM_CUPS] = {
  // strip, adr1, adr2, adr3, digi, anlg
  Cup(&strip1, 0,  1,  11, 23, A1),
  Cup(&strip1, 2,  3,  10, 25, A2),
  Cup(&strip1, 4,  5,  9,  27, A5),
  Cup(&strip1, 6,  7,  8,  29, A6),
  Cup(&strip1, 12, 13, 20, 35, A9),
  Cup(&strip1, 14, 15, 19, 33, A8),
  Cup(&strip1, 16, 17, 18, 31, A7),
  Cup(&strip1, 23, 24, 25, 37, A10),
  Cup(&strip1, 21, 22, 26, 39, A11),
  Cup(&strip1, 27, 28, 29, 41, A12)
};

Cup side2[NUM_CUPS] = {
  // strip, adr1, adr2, adr3, digi, anlg
  Cup(&strip2, 0,  1,  11, 43, A13),
  Cup(&strip2, 2,  3,  10, 45, A14),
  Cup(&strip2, 4,  5,  9,  47, A15),
  Cup(&strip2, 6,  7,  8,  10, A0),
  Cup(&strip2, 12, 13, 20, 11, A0),
  Cup(&strip2, 14, 15, 19, 12, A0),
  Cup(&strip2, 16, 17, 18, 13, A0),
  Cup(&strip2, 21, 22, 26, 49, A0),
  Cup(&strip2, 23, 24, 25, 51, A0),
  Cup(&strip2, 27, 28, 29, 53, A0)
};

bool side1CupFlag[NUM_CUPS] = {false};
bool side2CupFlag[NUM_CUPS] = {false};

// Button variables
long holdingTime;
long previousHoldingTime;
unsigned long firstButtonPressTime;
byte buttonState;
byte previousButtonState = LOW;

// Controller variables
unsigned long prevMillis = 0;
bool calibrating = false;
bool sensors_enabled = true;
int numPixels;

void calibrate() 
{
  int counter = 0;
  calibrating = true;

  // Set all cups to blue and reset calibration counter
  for (int j = STARTING_CUP; j < NUM_CUPS; j++) { 
    side1[j].turnGreen();
    side2[j].turnGreen();
    side1[j].resetCounter();
    side2[j].resetCounter();
  } 
  strip1.show();
  strip2.show();  
  delay(1000);

  while(counter < CAL_SEQ_COUNT) {
    for (long fph = 0; fph < 5 * 65536; fph += 256) // fph = FirstPixelHue
    { 
      // Update LED colours
      for (int i = 0; i < numPixels; i++) {
      int pixelHue = fph + (i * 65536L / numPixels);
      strip1.setPixelColor(i, strip1.gamma32(strip1.ColorHSV(pixelHue)));
      strip2.setPixelColor(i, strip2.gamma32(strip2.ColorHSV(pixelHue)));
      }

      // Check cup status asynchronously
      if ((millis() - prevMillis) > 50) {
        for (int j = STARTING_CUP; j < NUM_CUPS; j++) {
          side1[j].isCup();
          side2[j].isCup();
        }
        counter++;
        prevMillis = millis();
      }

      // Turn off unused cups
      for (int j = 0; j < STARTING_CUP; j++) {
        side1[j].turnOff();
        side2[j].turnOff();
      }      

      if (counter == CAL_SIDE_COUNT) { 
        // Set all cups to green
        for (int j = STARTING_CUP; j < NUM_CUPS; j++) { 
          side1[j].turnGreen();
          side2[j].turnGreen();
        } 
        strip1.show();
        strip2.show();  
        delay(10000);
      }
      else if (counter == CAL_SEQ_COUNT) {
        // Exit calibration sequence
        break;
      }
        
      strip1.show();
      strip2.show();
      delay(4);
    }
  }
  calibrating = false;
  sensors_enabled = true;
}

void setup() 
{
  // Enable serial printing
  Serial.begin(9600); 

  // Enable mux channels
  side2[3].setMuxChannel(3);
  side2[4].setMuxChannel(0);
  side2[5].setMuxChannel(1);
  side2[6].setMuxChannel(2);
  side2[7].setMuxChannel(5);
  side2[8].setMuxChannel(6);
  side2[9].setMuxChannel(4);

  // Initialise LED strips
  strip1.begin();
  strip1.setBrightness(250);

  strip2.begin();
  strip2.setBrightness(250);

  numPixels = strip1.numPixels();
  side2[6].enablePrinting();

  // Perform calibration sequence
  calibrate();

  // Configure button
  pinMode(SWITCH_PIN, INPUT);
}

void loop() 
{
  for (long fph = 0; fph < 5 * 65536; fph += 256) // fph = FirstPixelHue
  { 
    // Update LED colours
    for (int i = 0; i < numPixels; i++) {
      int pixelHue = fph + (i * 65536L / numPixels);
      strip1.setPixelColor(i, strip1.gamma32(strip1.ColorHSV(pixelHue)));
      strip2.setPixelColor(i, strip2.gamma32(strip2.ColorHSV(pixelHue)));
    }

    // Check cup status asynchronously
    if ((millis() - prevMillis) > 50) {
      for (int j = STARTING_CUP; j < NUM_CUPS; j++) {
        side1CupFlag[j] = side1[j].isCup() ? true : false;
        side2CupFlag[j] = side2[j].isCup() ? true : false;
      }
      prevMillis = millis();
    }

    // Update cup colours
    for (int j = 0; j < NUM_CUPS; j++) {
      if (j>=STARTING_CUP) {
        if ( !side1CupFlag[j] && sensors_enabled) side1[j].turnRed();
        if ( !side2CupFlag[j] && sensors_enabled) side2[j].turnBlue(); 
      } else {
        side1[j].turnOff();
        side2[j].turnOff();
      }
    }

    if (!calibrating) {
      checkButton();
    }
    
    strip1.show();
    strip2.show();
    delay(4);
  }
}

void checkButton() {
  buttonState = digitalRead(SWITCH_PIN);

  if (buttonState == HIGH && previousButtonState == LOW && (millis() - firstButtonPressTime) > 200) 
  {
    firstButtonPressTime = millis();
  }
  holdingTime = (millis() - firstButtonPressTime);

  if (holdingTime > 50) 
  {
    if (buttonState == HIGH && holdingTime > previousHoldingTime) 
    {
      Serial.println("button is pressed");
    }
    if (buttonState == LOW && previousButtonState == HIGH) 
    {
      if (holdingTime <= 3000)
      {
        Serial.println("short button press");
        sensors_enabled = !sensors_enabled;       
      }
      if (holdingTime > 3000) 
      {
        Serial.println("long button press");
        calibrate();
      }
    }
  }
   previousButtonState = buttonState;
   previousHoldingTime = holdingTime;
}