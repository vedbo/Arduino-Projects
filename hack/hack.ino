 
void setup() {
pinMode(6,OUTPUT);   //left motors   forward
pinMode(7,OUTPUT);   //left motors reverse
pinMode(8,OUTPUT);   //right   motors forward
pinMode(9,OUTPUT);   //right motors reverse
pinMode(1,OUTPUT);   //left motors   forward
pinMode(2,OUTPUT);   //left motors reverse
pinMode(3,OUTPUT);   //right   motors forward
pinMode(4,OUTPUT);   //right motors reverse
Serial.begin(9600);
 
}
 
void loop() {
  digitalWrite(1,LOW);
  digitalWrite(2,HIGH);
  digitalWrite(3,LOW);
  digitalWrite(4,HIGH);
  digitalWrite(6,LOW);
  digitalWrite(7,HIGH);
  digitalWrite(8,LOW);
  digitalWrite(9,HIGH);
    
}
