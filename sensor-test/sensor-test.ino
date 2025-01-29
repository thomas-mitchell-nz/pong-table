/* 
 * Filename: sensor-test.ino
 * FileType: Arduino source file
 * Author: Thomas Mitchell
 * Last modified: 31/7/2023
 * Description: Test script for ir sensors
 */

#define CUP 9

int D_PIN, A_PIN;

void setup() 
{
  Serial.begin(9600);  
  switch (CUP) {
    case 1:
      D_PIN = 23;
      A_PIN = A1;
      break;
    case 2:
      D_PIN = 25;
      A_PIN = A2;
      break;
    case 3:
      D_PIN = 27;
      A_PIN = A5;
      break;
    case 4:
      D_PIN = 29;
      A_PIN = A6;
      break;
    case 5:
      D_PIN = 35;
      A_PIN = A9;
      break;
    case 6:
      D_PIN = 33;
      A_PIN = A8;
      break;
    case 7:
      D_PIN = 31;
      A_PIN = A7;
      break;
    case 8:
      D_PIN = 37;
      A_PIN = A10;
      break;
    case 9:
      D_PIN = 39;
      A_PIN = A11;
      break;
    case 10:
      D_PIN = 41;
      A_PIN = A12;
      break;  
    case 11:
      D_PIN = 43;
      A_PIN = A13;
      break;
    case 12:
      D_PIN = 45;
      A_PIN = A14;
      break;
    case 13:
      D_PIN = 47;
      A_PIN = A15;
      break;
    case 14:
      D_PIN = 29;
      A_PIN = A6;
      break;
    case 15:
      D_PIN = 35;
      A_PIN = A9;
      break;
    case 16:
      D_PIN = 33;
      A_PIN = A8;
      break;
    case 17:
      D_PIN = 31;
      A_PIN = A7;
      break;
    case 18:
      D_PIN = 37;
      A_PIN = A10;
      break;
    case 19:
      D_PIN = 39;
      A_PIN = A11;
      break;
    case 20:
      D_PIN = 41;
      A_PIN = A12;
      break; 
  }
  pinMode(D_PIN ,OUTPUT); 
  pinMode(A_PIN, INPUT);
}

void loop() 
{ 
  digitalWrite(D_PIN, HIGH);
  delayMicroseconds(500); 
  Serial.println(analogRead(A_PIN));
  //digitalWrite(D_PIN,LOW);
  delay(100);
}
