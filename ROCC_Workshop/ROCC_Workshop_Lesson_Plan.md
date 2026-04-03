# ROCC Workshop: ESP32 + Firebase Cloud IoT

**Duration:** 60 - 75 minutes
**Objective:** Teach students how to stream real-time sensor data from an edge device (ESP32) to the cloud (Firebase) using the DHT11 Temperature & Humidity Sensor.

## Hardware Required (per group)
- 1x **ESP32 Development Board** (Elegoo USB-C version)
- 1x **DHT11 Sensor Module** (HiLetgo 3-pin version)
- 3x **Female-to-Male Jumper Wires** (Dupont cables)
- 1x **USB-C Data Cable**
- *Optional: Breadboard (for cleaner setup)*

---

## Lesson Flow

### Part 1: Introduction & Hardware Setup (15 Minutes)
**The Concept:** Explain that the ESP32 acts as the "Edge" IoT device, collecting physical data, while Firebase acts as the "Backend-as-a-Service" (BaaS).
**The Wiring:**
The HiLetgo DHT11 module has 3 pins. Have students use the jumper wires to connect it directly to the ESP32:
1. **`+` or `VCC`** ➡️ Connect to the `3V3` pin on the ESP32.
2. **`-` or `GND`** ➡️ Connect to any `GND` pin on the ESP32.
3. **`OUT` or `DATA`** ➡️ Connect to `GPIO 15` (labeled `D15` or `15`) on the ESP32.

### Part 2: Firebase Console Setup (20 Minutes)
This is the core "Cloud" portion of the workshop.
1. Have students navigate to [console.firebase.google.com](https://console.firebase.google.com/) and create a new project (e.g., "ROCC-Workshop-Demo").
2. Disable Google Analytics (to save setup time).
3. On the left sidebar, go to **Build > Realtime Database**.
4. Click **Create Database** (Start in **Test Mode**).
5. **CRITICAL STEP:** Go to the "Rules" tab of the database and ensure both `.read` and `.write` are set to `true`. This allows us to bypass complex authentication for a beginner workshop.
6. Have students copy two things and paste them into a notepad:
   - **Database URL:** Located at the top of the Data tab (e.g., `https://rocc-workshop-demo-default-rtdb.firebaseio.com/`).
   - **Web API Key:** Go to Project Settings (Gear icon) > General > Web API Key.

### Part 3: Software & Libraries (15 Minutes)
Ask students to open the Arduino IDE.
1. Set up the ESP32 Board Manager if not already done.
2. Go to **Sketch > Include Library > Manage Libraries**.
3. Install the **"DHT sensor library" by Adafruit** (and install the "Adafruit Unified Sensor" dependency if prompted).
4. Install the **"Firebase ESP32 Client" by Mobizt**.

### Part 4: The Code & "The Magic Moment" (25 Minutes)
Distribute the provided `ROCC_Workshop.ino` skeleton code to the students.
1. Have students fill in their Wi-Fi SSD and Password.
2. Have students paste their specific `API_KEY` and `DATABASE_URL`.
3. Have students compile and upload the sketch to the ESP32.
4. Open the Arduino Serial Monitor (baud rate 115200) to verify data is being read locally.
5. **The Magic Moment:** Have students open the Firebase Realtime Database in their web browser. They will see the data magically appear and update live every 5 seconds as the ESP32 pushes new temperature and humidity readings!

---

## Pro-Tips for the Instructor
- **USB Cables:** The most common issue is students using "charging-only" USB-C cables instead of data cables. Remind them to use a cable capable of data transfer.
- **Port Selection:** If the ESP32 doesn't show up in the Arduino port list, they may need to install the CP210x driver for the Elegoo boards. Have the driver link handy.
- **Troubleshooting:** If Firebase returns an error, the 99% cause is an incorrect Database URL (should not have a trailing slash) or Database Rules not being set to `true`.
