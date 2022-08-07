int a;

void setup() 
{
  Serial.begin(9600); 
  pinMode(25,OUTPUT); 
}

void loop() 
{ 
  digitalWrite(25,HIGH); 
  delayMicroseconds(500); 
  a=analogRead(A2);
  Serial.println(a); 
  delay(100);
}
