/* 
 * Filename: Cup.cpp
 * FileType: C++ source file
 * Author: Thomas Mitchell
 * Last modified: 23/8/2023
 * Description: Cup class for interfacing with 
 *    LEDs and sensors indidual cup
 */

#include "Cup.h"
#include <Adafruit_NeoPixel.h>

Cup::Cup(Adafruit_NeoPixel *strip, int adr1, int adr2, int adr3, int digi, int anlg) {
  stripPtr = strip;
  ledAdr1 = adr1;
  ledAdr2 = adr2;
  ledAdr3 = adr3;
  digitalOut = digi;
  analogIn = anlg;
  
  pinMode(digitalOut, OUTPUT);
  pinMode(analogIn, INPUT);
  pinMode(S0, OUTPUT); 
  pinMode(S1, OUTPUT); 
  pinMode(S2, OUTPUT); 

  digitalWrite(S0, LOW);
  digitalWrite(S1, LOW);
  digitalWrite(S2, LOW);
}

void Cup::setColour(int R, int G, int B) {
  stripPtr->setPixelColor(ledAdr1, R, G, B);
  stripPtr->setPixelColor(ledAdr2, R, G, B);
  stripPtr->setPixelColor(ledAdr3, R, G, B);
}

void Cup::turnRed() {
  this->setColour(255,0,0);
}

void Cup::turnBlue() {
  this->setColour(0,0,255);
}

void Cup::turnGreen() {
  this->setColour(0,255,0);
}

void Cup::turnOff() {
  this->setColour(0,0,0);
}

void Cup::enablePrinting() {
  print = true;
}

int Cup::pulse() {
  int val; 

  if (muxEnabled) {
    // Loop through the 3 mux signals
    for(int i = 0; i < 3; i ++){
      digitalWrite(controlPin[i], muxChannelArray[muxChannel][i]);
    }
    // Pulse IR emitter
    digitalWrite(digitalOut,HIGH); 
    delayMicroseconds(500); 
    val = analogRead(MUX_PIN);
  } else {
    digitalWrite(digitalOut,HIGH); 
    delayMicroseconds(500); 
    val = analogRead(analogIn);
  }
  return val;
}

bool Cup::isCup() {
  int val, avg;

  // Get moving average
  val = pulse();
  sum = sum - READINGS[index];       // Remove the oldest entry from the sum
  READINGS[index] = val;             // Add the newest reading to the window
  sum = sum + val;                   // Add the newest reading to the sum
  index = (index+1) % BUFFER_SIZE;   // Increment the index, and wrap to 0 if it exceeds the window size
  avg = sum / BUFFER_SIZE;

  /* Set the noCupThresh and isCupThresh values during the calibration sequence.
   * Performing this operation outside of this function caused errors
   * to accumulate, ultimately leading to inaccurate filter thresholds.
   */
  if (counter == CAL_SIDE_COUNT) {
    // Set no cup value
    buffer += avg;
    isCupThresh = round((float) buffer / CAL_SIZE);
    buffer = 0;
  }
  else if (counter == CAL_SEQ_COUNT) {
    // Set is cup value
    buffer += avg;
    noCupThresh = round((float) buffer / CAL_SIZE);
    buffer = 0;
  }
  else if (counter > BUFFER_SIZE && counter < CAL_SEQ_COUNT) {
    buffer += avg;
  } 

  if (counter <= CAL_SEQ_COUNT) {
    counter++;
  }

  if (print) {
    char str[150];
    sprintf(str, "avg: %d  noCupThresh: %d  isCupThresh: %d",
        avg, noCupThresh, isCupThresh);
    Serial.println(str);
  }

  return checkForCup(avg);
}

void Cup::resetCounter() {
  counter = 0;
}

bool Cup::checkForCup(int val) {
  // Adjust noCupThresh to maintain a gap if it's equal to isCupThresh
  if (noCupThresh == isCupThresh)
    noCupThresh = isCupThresh - 1;

  // Calculate the half of the absolute difference between noCupThresh and isCupThresh
  int diff = round((float) abs(noCupThresh - isCupThresh) / 2);
  
  // Ensure a minimum diff of 1 to avoid potential division by zero
  if (diff == 0)
    diff = 1;

  // Determine cup presence based on the comparison of noCupThresh and isCupThresh
  if (noCupThresh < isCupThresh)
    return val >= (noCupThresh + diff);
  else
    return val <= (noCupThresh - diff);
}

void Cup::setMuxChannel(int channel) {
  muxChannel = channel;
  muxEnabled = true;
}

// For testing purposes
int Cup::readMux(int channel) {
  int controlPin[] = {S0, S1, S2};

  int muxChannelArray[8][3] = {
    {0,0,0}, //channel 0
    {1,0,0}, //channel 1
    {0,1,0}, //channel 2
    {1,1,0}, //channel 3
    {0,0,1}, //channel 4
    {1,0,1}, //channel 5
    {0,1,1}, //channel 6
    {1,1,1}  //channel 7
  };

  // Loop through the 3 signals
  for(int i = 0; i < 3; i ++){
    digitalWrite(controlPin[i], muxChannelArray[muxChannel][i]);
  }
  
  // Pulse IR emitter
  digitalWrite(digitalOut,HIGH); 
  delayMicroseconds(500); 
  
  // Read the value at the mux pin
  return analogRead(MUX_PIN);;
}