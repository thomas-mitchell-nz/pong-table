#ifndef Cup_h
#define Cup_h

/* 
 * Filename: Cup.h
 * FileType: C++ header file
 * Author: Thomas Mitchell
 * Last modified: 23/8/2023
 * Description: Cup class header
 */
 
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

// Mux control pins
#define MUX_PIN A0
#define S0      9
#define S1      8
#define S2      7

// Buffer windows
#define BUFFER_SIZE     10
#define CAL_SIZE        100
#define CAL_SIDE_COUNT  CAL_SIZE+BUFFER_SIZE
#define CAL_SEQ_COUNT   2*CAL_SIZE+BUFFER_SIZE

class Cup {
  private:
    void setColour(int R, int G, int B);
    bool checkForCup(int val);
    int readMux(int channel);
    int pulse();

    bool print = false;

    // LEDs
    Adafruit_NeoPixel *stripPtr;
    int ledAdr1, ledAdr2, ledAdr3;

    // IR sensors 
    int digitalOut;
    int analogIn;

    // Digital filter
    int counter = 0;
    long buffer = 0;
    int isCupThresh = 0;
    int noCupThresh = 0;

    // Moving average
    int READINGS[BUFFER_SIZE];
    int sum = 0;
    int index = 0;

    // Mux
    int muxChannel = 0;
    bool muxEnabled = false;
    int controlPin[3] = {S0, S1, S2};
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
    
  public:
    Cup(Adafruit_NeoPixel *strip, int adr1, int adr2, int adr3, int digi, int anlg);
    void setMuxChannel(int channel);
    void enablePrinting();
    void resetCounter();
    void turnRed();
    void turnBlue();
    void turnGreen();
    void turnOff();
    bool isCup();
};

#endif