void setup() {
  Serial.begin(115200);
  pinMode(15, INPUT);  // GPIO15 as input
  Serial.println("Touch sensor test - touch it now!");
}

void loop() {
  int value = digitalRead(15);
  Serial.print("Touch value: ");
  Serial.println(value);  // Should be 0 (not touched) or 1 (touched)
  delay(200);
}