#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "YourWiFiSSID";
const char* password = "YourWiFiPassword";
const char* serverUrl = "http://yourserver.com/addData"; // URL to your server endpoint

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(2, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(2, HIGH);  // turn the LED on (HIGH is the voltage level)

  // Collect your data, for example:
  float temperature = 25.5;
  float humidity = 60.0;

  // Create JSON object
  StaticJsonDocument<200> jsonDoc;
  jsonDoc["temperature"] = temperature;
  jsonDoc["humidity"] = humidity;

  // Serialize JSON to string
  String jsonString;
  serializeJson(jsonDoc, jsonString);

  // Send data to server
  HTTPClient http;
  http.begin(serverUrl);
  http.addHeader("Content-Type", "application/json");

  int httpResponseCode = http.POST(jsonString);

  if (httpResponseCode > 0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
  } else {
    Serial.print("Error sending POST request: ");
    Serial.println(httpResponseCode);
  }

  http.end();

  delay(60000); // Wait for 1 minute before sending next data point
}