#include <Wire.h>


#define brake 2
#define motor 5
#define dir 3 //left grey pin


void setup()  {
  Serial.begin(9600);

  pinMode(brake, OUTPUT);
  pinMode(motor, OUTPUT);
  pinMode(dir, OUTPUT);
}

void loop()  {

  //individual motor component level validation - basic speed control, directionality, and braking

  //forwards direction
  digitalWrite(dir, HIGH); // direction
  for (int i = 0; i <255; i++) {
    analogWrite(motor, 80);
    delay(10);
  }
  digitalWrite(brake, LOW); // engage brake
  delay(2000);  
  digitalWrite(brake, HIGH); //disengages brake
  delay(1000);

  //backwards direction
  digitalWrite(dir, LOW); // direction
  for (int i = 0; i <255; i++) {
    analogWrite(motor, 80);
    delay(10);
  }
  digitalWrite(brake, LOW); // engage brake
  delay(2000);  
  digitalWrite(brake, HIGH); //disengages brake
  delay(1000);
}
