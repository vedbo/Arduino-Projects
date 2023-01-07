char t;
 
void setup() {
pinMode(6,OUTPUT);   //left motors   forward
pinMode(7,OUTPUT);   //left motors reverse
pinMode(8,OUTPUT);   //right   motors forward
pinMode(9,OUTPUT);   //right motors reverse
pinMode(2 ,OUTPUT);    //Led
pinMode(3, OUTPUT);
pinMode(4,OUTPUT);
pinMode(5,OUTPUT);
Serial.begin(9600);
 
}
 
void loop() {
if(Serial.available()){
   t = Serial.read();
  Serial.println(t);
}
 
   
if(t == 'L'){      //turn right (left side motors rotate in forward direction,   right side motors doesn't rotate)
   digitalWrite(6, HIGH);
  digitalWrite(7, LOW);
  digitalWrite(8, HIGH);
  digitalWrite(9, LOW);
  digitalWrite(2, HIGH);
  digitalWrite(3, LOW);
  digitalWrite(4, HIGH);
  digitalWrite(5, LOW);

}
 
 
else if(t == 'S'){      //STOP (all motors stop)
   digitalWrite(5,LOW);
  digitalWrite(6,LOW);
  digitalWrite(7,LOW);
   digitalWrite(8,LOW);
   digitalWrite(2,LOW);
  digitalWrite(3,LOW);
  digitalWrite(4,LOW);
   digitalWrite(9,LOW);
}
delay(100);
}