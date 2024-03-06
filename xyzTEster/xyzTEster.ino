#include <Wire.h>

const int MPU_ADDR = 0x68;
const int BUZZER_PIN = 9; // Buzzer pin

int16_t accX, accY, accZ;
int16_t prevAccX, prevAccY, prevAccZ;

// Calibration values
int16_t accX_offset, accY_offset, accZ_offset;

// Acceleration threshold for buzzer
const int ACCEL_THRESHOLD = 8000; // Adjust this value as needed

// Function prototypes
void readAccelData();
void calibrateAccelerometer();

void setup() {
  Serial.begin(9600);
  Wire.begin();

  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);

  // Calibrate the accelerometer
  calibrateAccelerometer();

  pinMode(BUZZER_PIN, OUTPUT); // Initialize the buzzer pin
}

void loop() {
  readAccelData();

  // Apply calibration offsets
  accX -= accX_offset;
  accY -= accY_offset;
  accZ -= accZ_offset;

  // Check if there is a sudden change in acceleration
  int16_t accXDiff = abs(accX - prevAccX);
  int16_t accYDiff = abs(accY - prevAccY);
  int16_t accZDiff = abs(accZ - prevAccZ);

  if (accXDiff > ACCEL_THRESHOLD || accYDiff > ACCEL_THRESHOLD || accZDiff > ACCEL_THRESHOLD) {
    // Sound the buzzer
    tone(BUZZER_PIN, 2000, 100); // Adjust the frequency and duration as needed
  }

  // Update previous acceleration values
  prevAccX = accX;
  prevAccY = accY;
  prevAccZ = accZ;

  Serial.print("Accelerometer: ");
  Serial.print("X = "); Serial.print(accX);
  Serial.print(" Y = "); Serial.print(accY);
  Serial.print(" Z = "); Serial.println(accZ);

  delay(500);
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