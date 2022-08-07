// Cup.h
#ifndef Cup_h
#define Cup_h

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

class Cup {
  private:
    void setColour (int R, int G, int B);
    
    int readMux(int channel);
    int pulse ();

    Adafruit_NeoPixel *strip;
    int ledAdr1;
    int ledAdr2;
    int ledAdr3;
    int digiPin;
    int analPin;
    int mux;
    int channel;
    int threshold;
    
  public:
    Cup(Adafruit_NeoPixel *_strip, int adr1, int adr2, int adr3, int _digiPin, int _analPin, bool mux=false, int channel=0);
    void turnRed ();
    void turnGreen ();
    void turnBlue ();
    void turnOff ();
    int getState ();
    void calibrate ();
    bool checkForCup ();

    bool printSignal = false;
    bool cupPresent;
};

#endif
