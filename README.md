# Arduino Projects Repository

Welcome to the collection of my Arduino projects and sketches! This repository contains various hardware and IoT experiments. Below is a summary of some of the key projects included in this repository.

## Key Projects

### 🐕 Dog Health Monitor (`FINALGSRFIREBASE`)
An IoT-enabled health monitor designed for dogs using an ESP32. 
- **Sensors Used**: MPU6050 (Accelerometer/Gyroscope) for activity tracking, Touch Sensor, and simulated heart rate detection.
- **Features**: 
  - Connects to Wi-Fi and streams real-time data to a Firebase Realtime Database.
  - Detects high physical activity and danger modes (e.g., abnormally high heart rates).
  - Built using `FirebaseESP32` and `MPU6050` libraries.

### 💧 Water Sensor Test (`Water_sensortest`)
A standalone sketch for interfacing with and reading data from water/moisture sensors to detect the presence of liquid.

### 📟 Keypad Integration (`KEYPAD`)
A project that involves reading inputs from a matrix keypad, which can be useful for security locks or menu navigation on an LCD.

### 🌐 Web Server & GSR (`GSRWEBServer` & `GSRTEST`)
Galvanic Skin Response (GSR) sensor tests and an implementation involving a web server to host/serve the sensor readings locally over a network.

### 🛠️ Hackathon Sketches (`HACK1`, `hack`, `hack3`)
Various rapid-prototyping sketches built during hackathons, experimenting with different sensors and actuators.

### 📚 Libraries (`libraries`)
Contains the local copies of necessary Arduino libraries required to compile these sketches, including `FirebaseESP32`, `DHTStable`, `LCD03`, `MPU6050`, `WiFiNINA_Generic`, and `EspSoftwareSerial`.

---

*Note: The commit history of this repository has been preserved to reflect the original creation dates of these projects.*
