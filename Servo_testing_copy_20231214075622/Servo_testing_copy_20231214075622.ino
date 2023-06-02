#include <Servo.h>

Servo distanceChecker;
Servo microServo;

double duration;
double distance;

const int echoPin = 11;
const int trigPin = 12;
 // Distance threshold to activate the servo motor

void setup() {
  Serial.begin(9600);

  distanceChecker.attach(31);
  distanceChecker.write(0);

  microServo.attach(6); // Pin connected to the servo motor

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.begin(9600);
}

void loop() {
  distanceChecker.write(0);
  distanceChecker.write(90);

  digitalWrite(trigPin, LOW);
  digitalWrite(trigPin, HIGH);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  Serial.print("Distance = ");
  Serial.println(distance);

  if (distance >= 50) {
    microServo.write(0); // Rotate the servo motor to 180 degrees if the distance is greater than or equal to the threshold
    delay(100);
  } else {
    microServo.write(90); // Rotate the servo motor to 90 degrees if the distance is less than the threshold
    delay(100);
  }

  delay(100);
}
