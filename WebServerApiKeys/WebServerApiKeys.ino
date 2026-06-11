#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
 
const char* ssid = "iot-emp2"                 //domän namn
const char* password = "iot123456";           //
 
const char* server = "http://10.67.1.130:8000/m"          // placeholder
const char* apiKey = "test"
 
void setup() {
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
  }
 
  HTTPClient http;
  WiFiClient client;
 
  http.begin(client, server);
 
  http.addHeader("_api_key", apiKey);
 
  int httpCode = http.GET();
 
  String payload = http.getString();
 
  Serial.println(httpCode);
  Serial.println(payload);  // debug läge Serial print för att reda ut problem
 
  http.end();
}
 
void loop() {}
