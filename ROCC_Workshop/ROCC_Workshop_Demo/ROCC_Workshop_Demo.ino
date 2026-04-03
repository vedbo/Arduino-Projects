#include <WiFi.h>
#include <FirebaseESP32.h>
#include <DHT.h>

// Provide the token generation process info.
#include <addons/TokenHelper.h>
// Provide the RTDB payload printing info and other helper functions.
#include <addons/RTDBHelper.h>

/* ======================================================== */
/* 1. FILL IN YOUR WIFI CREDENTIALS BELOW                   */
/* ======================================================== */
#define WIFI_SSID "YOUR_WIFI_NETWORK_NAME"
#define WIFI_PASSWORD "YOUR_WIFI_PASSWORD"

/* ======================================================== */
/* 2. FILL IN YOUR FIREBASE DETAILS BELOW                   */
/* ======================================================== */
// Go to Firebase Project Settings (Gear Icon) -> General -> Web API Key
#define API_KEY "YOUR_API_KEY_HERE"

// Go to Realtime Database -> Data -> Copy the URL at the top
// Make sure to remove "https://" and any trailing slashes ("/")!
// Example: "your-project-name-default-rtdb.firebaseio.com"
#define DATABASE_URL "YOUR_PROJECT_ID-default-rtdb.firebaseio.com"


/* ======================================================== */
/* DO NOT EDIT BELOW THIS LINE UNLESS YOU KNOW WHAT YOU DO! */
/* ======================================================== */

// DHT11 Sensor Configuration
#define DHTPIN 15      // Digital pin connected to the DHT sensor (GPIO 15)
#define DHTTYPE DHT11  // Which DHT sensor we are using

DHT dht(DHTPIN, DHTTYPE);

// Define Firebase Data object
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;

void setup() {
  Serial.begin(115200);

  // Initialize the DHT11 sensor
  dht.begin();

  // Connect to Wi-Fi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());

  // Firebase Configuration
  // Note: When using test_mode / NoAuth, we must NOT provide an api_key, 
  // otherwise Firebase rejects the REST API request with "400 Bad Request".
  // config.api_key = API_KEY; 
  config.database_url = DATABASE_URL;

  // Since Realtime Database Rules are set to true, we can bypass Auth entirely.
  // This prevents the "INVALID_EMAIL" error requiring Console activation.
  config.signer.test_mode = true;
  config.token_status_callback = tokenStatusCallback;

  // Required since v4.4.x: Set SSL buffer size for secure connections
  fbdo.setBSSLBufferSize(4096, 1024);

  // Initialize Firebase connection
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

  Serial.println("====================================");
  Serial.println("  ROCC Firebase ESP32 Workshop Ready");
  Serial.println("====================================");
}

void loop() {
  // Wait 5 seconds between measurements
  if (Firebase.ready() && (millis() - sendDataPrevMillis > 5000 || sendDataPrevMillis == 0)) {
    sendDataPrevMillis = millis();

    // Read temperature and humidity from DHT11
    float humidity = dht.readHumidity();
    float temperatureCelsius = dht.readTemperature();         // Read temperature as Celsius
    float temperatureFahrenheit = dht.readTemperature(true);  // Read temperature as Fahrenheit

    // Check if any reads failed
    if (isnan(humidity) || isnan(temperatureCelsius) || isnan(temperatureFahrenheit)) {
      Serial.println("Failed to read from DHT sensor! Check your wiring.");
      return;
    }

    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.print("%  |  Temperature: ");
    Serial.print(temperatureFahrenheit);
    Serial.println("°F");

    Serial.println("Streaming data to Firebase Cloud...");

    // Create a JSON object to send multiple values at once
    FirebaseJson json;
    json.set("temperatureF", temperatureFahrenheit);
    json.set("temperatureC", temperatureCelsius);
    json.set("humidity", humidity);

    // Push the JSON object to the "rocc_sensor_node" path in the database
    if (Firebase.setJSON(fbdo, "/rocc_sensor_node", json)) {
      Serial.println("  ✓ Success! Data is in the cloud!");
    } else {
      Serial.println("  ❌ Failed to send data: " + fbdo.errorReason());
    }

    Serial.println("------------------------------------");
  }
}
