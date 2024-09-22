// Sensor pin
const int sensorPin = 7;

void setup() {
  // Set pin 7 as an INPUT with pull-up resistor enabled
  pinMode(sensorPin, INPUT_PULLUP);
  
  Serial.begin(115200);
}

void loop() {
  // Get the reading from the function below and print it
  bool isWet = readSensor();
  
  Serial.print("Sensor status: ");
  Serial.println(isWet ? "Wet" : "Dry");
  
  delay(1000);
}

// This is a function used to get the reading
bool readSensor() {
  int sensorValue = digitalRead(sensorPin);
  return (sensorValue == LOW);  // Return true if wet (LOW), false if dry (HIGH)
}