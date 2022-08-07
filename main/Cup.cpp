// Cup.cpp
#include "Cup.h"
#include <Adafruit_NeoPixel.h>

//Mux control pins
int s0 = 9;
int s1 = 8;
int s2 = 7;

//Mux in "Z" pin
int Z_pin = A0;

Cup::Cup(Adafruit_NeoPixel *_strip, int adr1, int adr2, int adr3, int _digiPin, int _analPin, bool _mux=false, int _channel) {
  strip = _strip;
  digiPin = _digiPin;
  analPin = _analPin;
  ledAdr1 = adr1;
  ledAdr2 = adr2;
  ledAdr3 = adr3;
  mux = _mux;
  channel = _channel;
  
  pinMode(digiPin,OUTPUT);
  pinMode(s0, OUTPUT); 
  pinMode(s1, OUTPUT); 
  pinMode(s2, OUTPUT); 

  digitalWrite(s0, LOW);
  digitalWrite(s1, LOW);
  digitalWrite(s2, LOW);
}

void Cup::turnRed () {
  setColour (255,0,0);
}

void Cup::turnGreen () {
  setColour (0,255,0);
}

void Cup::turnBlue () {
  setColour (0,0,255);
}

void Cup::turnOff () {
  setColour (0,0,0);
}

void Cup::setColour (int R, int G, int B) {
  strip->setPixelColor(ledAdr1, R, G, B);
  strip->setPixelColor(ledAdr2, R, G, B);
  strip->setPixelColor(ledAdr3, R, G, B);
}


void Cup::calibrate () {
  int backgroundVal = pulse();
  int tol = backgroundVal * 0.01; // 20% of background
  threshold = backgroundVal - tol;
  cupPresent = true;
}

int Cup::pulse () {
  int val;

  if (mux == false) {
      digitalWrite(digiPin,HIGH); 
      delayMicroseconds(500); 
      val = analogRead(analPin);
  } else {
    readMux(channel);
  }

  if (printSignal) Serial.println(val);
  return val;
}

bool Cup::checkForCup () {
  int val = pulse();
  return (val < threshold);
}


int Cup::readMux(int channel) {
  int controlPin[] = {s0, s1, s2};

  int muxChannel[8][3]={
    {0,0,0}, //channel 0
    {1,0,0}, //channel 1
    {0,1,0}, //channel 2
    {1,1,0}, //channel 3
    {0,0,1}, //channel 4
    {1,0,1}, //channel 5
    {0,1,1}, //channel 6
    {1,1,1}, //channel 7
  };

  //loop through the 3 sig
  for(int i = 0; i < 3; i ++){
    digitalWrite(controlPin[i], muxChannel[channel][i]);
  }
  
  // pulse ir emitter
  digitalWrite(digiPin,HIGH); 
  delayMicroseconds(500); 
  
  //read the value at the Z pin
  int val = analogRead(Z_pin);
  
  //return the value
  return val;
}
