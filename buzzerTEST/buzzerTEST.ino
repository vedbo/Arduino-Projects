#include <Wire.h>

const int MPU_ADDR = 0x68;
const int buzzer = 9; // Buzzer connected to pin 9

int16_t accX, accY, accZ;
int16_t gyroX, gyroY, gyroZ;

// Calibration values
int16_t accX_offset, accY_offset, accZ_offset;

// Threshold values for fall detection
const int16_t fallThreshold = 1800; // Adjust this value as needed
const int16_t movementThreshold = 800; // Adjust this value as needed

void setup() {
  Serial.begin(9600);
  Wire.begin();
  pinMode(buzzer, OUTPUT); // Set buzzer pin as output

  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);

  // Calibrate the accelerometer
  calibrateAccelerometer();
}

void loop() {
  readAccelData();

  // Apply calibration offsets
  accX -= accX_offset;
  accY -= accY_offset;
  accZ -= accZ_offset;

  // Check for sudden movement or potential fall
  if (checkSuddenMovement()) {
    Serial.println("Sudden movement detected!");
    triggerBuzzer();
  }

  Serial.print("Accelerometer: ");
  Serial.print("X = "); Serial.print(accX);
  Serial.print(" Y = "); Serial.print(accY);
  Serial.print(" Z = "); Serial.println(accZ);

  delay(100); // Adjust delay as needed
}

bool checkSuddenMovement() {
  // Calculate the total acceleration magnitude
  int16_t totalAcceleration = sqrt(sq(accX) + sq(accY) + sq(accZ));

  // Check if the total acceleration exceeds the movement threshold
  if (totalAcceleration > movementThreshold) {
    // Check if the acceleration in any axis exceeds the fall threshold
    if (abs(accX) > fallThreshold || abs(accY) > fallThreshold || abs(accZ) > fallThreshold) {
      return true; // Potential fall detected
    }
  }

  return false; // No sudden movement or fall detected
}

void readAccelData() {
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDR, 6, true);

  accX = Wire.read() << 8 | Wire.read();
  accY = Wire.read() << 8 | Wire.read();
  accZ = Wire.read() << 8 | Wire.read();
}

void calibrateAccelerometer() {
  int16_t accX_sum = 0, accY_sum = 0, accZ_sum = 0;
  uint8_t samples = 100;

  Serial.println("Calibrating accelerometer...");

  for (uint8_t i = 0; i < samples; i++) {
    readAccelData();
    accX_sum += accX;
    accY_sum += accY;
    accZ_sum += accZ;
    delay(10);
  }

  accX_offset = -accX_sum / samples;
  accY_offset = -accY_sum / samples;
  accZ_offset = (accZ_sum / samples) - 16384; // Account for 1g acceleration

  Serial.print("Accelerometer offsets: ");
  Serial.print("X = "); Serial.print(accX_offset);
  Serial.print(" Y = "); Serial.print(accY_offset);
  Serial.print(" Z = "); Serial.println(accZ_offset);
}

void triggerBuzzer() {
  tone(buzzer, 1000); // Send 1KHz sound signal
  delay(1000); // Buzzer on for 1 second
  noTone(buzzer); // Stop sound
}