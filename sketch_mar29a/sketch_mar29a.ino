#include <Servo.h>

Servo myservo; 
Servo myservo1; 
Servo myservo2; 
int pos = 0;    // variable to store the servo position
char t;
int j = 0;

void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  myservo1.attach(13);
  myservo2.attach(3);
  Serial.begin(9600); // initialize serial communication at 9600 bits per second
}

void loop() {
  if (Serial.available()) {
    t = Serial.read();
    Serial.println(t);
  }

  if (t == 'a') { 

      myservo.write(90);              // tell servo to go to position in variable 'pos'
                   // waits 15 ms for the servo to reach the position
    }
   else if (t == 'b') {
// goes from 180 degrees to 0 degrees
j++;
      myservo.write(25);              // tell servo to go to position in variable 'pos'
                    // waits 15 ms for the servo to reach the position
  }else if (t == 'c'){
    myservo1.write(25);
  } else if (t == 'd'){
    myservo1.write(225);
  } else if (t == 'e'){
    myservo2.write(90);
  } else if (t == 'f'){
    myservo2.write(270);
  }
}
