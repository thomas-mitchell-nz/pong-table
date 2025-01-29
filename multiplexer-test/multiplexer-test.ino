/* 
 * Filename: multiplexer-test.ino
 * FileType: Arduino source file
 * Author: Thomas Mitchell
 * Last modified: 31/7/2023
 * Description: Test script for mux
 */

#define CHANNEL 4
#define D_PIN 13

// Mux control pins
int s0 = 9;
int s1 = 8;
int s2 = 7;

// Mux in "Z" pin
int Z_pin = A0;

void setup(){
  pinMode(s0, OUTPUT); 
  pinMode(s1, OUTPUT); 
  pinMode(s2, OUTPUT); 

  digitalWrite(s0, LOW);
  digitalWrite(s1, LOW);
  digitalWrite(s2, LOW);

  pinMode(D_PIN,OUTPUT);   
  Serial.begin(9600);
}

void loop()
{
  // Loop through and read all 8 values
  for(int i = CHANNEL; i < CHANNEL+1; i ++){
    Serial.print("Value at channel ");
    Serial.print(i);
    Serial.print(" is : ");
    Serial.println(readMux(CHANNEL));
  }

  Serial.println("******************************");
  delay(200);
}

int readMux(int channel){
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
  digitalWrite(D_PIN,HIGH); 
  delayMicroseconds(500);
  
  //read the value at the Z pin
  int val = analogRead(Z_pin);

  digitalWrite(D_PIN,LOW); 

  return val;
}
