#include <WiFi.h>
#include <WebServer.h>

// Wi-Fi credentials
const char* ssid = "ORBI14";
const char* password = "jollytable496";

// Web server on port 80
WebServer server(80);

const int LED_PIN = 13;
const int GSR_PIN = 39;

void handleRoot() {
  int sensorValue = analogRead(GSR_PIN);
  float conductiveVoltage = sensorValue * (3.3 / 4095.0);
  String html = "<!DOCTYPE html><html><head><meta http-equiv='refresh' content='1'></head><body>Sensor Value: " + String(sensorValue) + "</body></html>";
  server.send(200, "text/html", html);
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  delay(1000);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  // Print the IP address
  Serial.println("Connected to WiFi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Start the web server
  server.on("/", handleRoot);
  server.begin();
  Serial.println("Web server started");
}

void loop() {
  server.handleClient();

  // Print the sensor value every 5 seconds
  static unsigned long lastPrintTime = 0;
  unsigned long currentTime = millis();
  if (currentTime - lastPrintTime >= 5000) {
    int sensorValue = analogRead(GSR_PIN);
    Serial.print("Sensor Value: ");
    Serial.println(sensorValue);
    lastPrintTime = currentTime;
  }
}