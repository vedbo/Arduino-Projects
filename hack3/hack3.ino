char t;
#include <Servo.h>

Servo distanceChecker;

int pos = 0;

double duration;

double distance;

const int echoPin = 37;

const int trigPin = 39;



void setup() {
Serial.begin(9600);

  distanceChecker.attach(31);

  distanceChecker.write(0);

  pinMode(trigPin, OUTPUT);

  pinMode(echoPin, INPUT);

  Serial.println("Ready to sense!");


pinMode(6,OUTPUT);   
pinMode(7,OUTPUT);   
pinMode(8,OUTPUT);  
pinMode(9,OUTPUT);   
pinMode(2 ,OUTPUT);    
pinMode(3, OUTPUT);
pinMode(4,OUTPUT);
pinMode(5,OUTPUT);
pinMode(10, OUTPUT);

Serial.begin(9600);
 
}
 
void loop() {
  distanceChecker.write(0);

  distanceChecker.write(90);


  digitalWrite(trigPin, LOW);


  digitalWrite(trigPin, HIGH);


  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  distance = duration * 0.034/2;

  Serial.print("Distance= ");

  Serial.println(distance);

if (distance >= 30) {
  digitalWrite(6, HIGH);
  digitalWrite(7, LOW);
  digitalWrite(8, HIGH);
  digitalWrite(9, LOW);
  digitalWrite(2, HIGH);
  digitalWrite(3, LOW);
  digitalWrite(4, HIGH);
  digitalWrite(5, LOW);
  delay(100);
} 
else if (distance <= 30 and distance >= 18) {
  digitalWrite(6, HIGH);
    digitalWrite(7, HIGH);
    digitalWrite(8, LOW);
    digitalWrite(9, HIGH);
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
    digitalWrite(5, HIGH);
    pinMode(10, HIGH);

  delay(100);
}
else if (distance <= 18) {     
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
   pinMode(10, HIGH);
  delay(100);
}

delay(100);
}