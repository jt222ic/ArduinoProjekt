void setup() {
  Serial.begin(115200);
  delay(10);
 
  Serial.println("\nAnsluter till WiFi...");
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  Serial.println("\nAnsluten till WiFi!");
  Serial.print("IP-adress: ");
  Serial.println(WiFi.localIP());
}
 
void loop() {
  unsigned long currentMillis = millis();
  
  // Kontrollera om det är dags att hämta vädret igen
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    getWeather();
  }
}
 
void getWeather() {
  // Kontrollera att vi fortfarande är anslutna
  if (WiFi.status() == WL_CONNECTED) {
 
    // Skapa en WiFiClientSecure-pekare (för HTTPS)
    std::unique_ptr<BearSSL::WiFiClientSecure> client(new BearSSL::WiFiClientSecure);
    
    // **VIKTIGT OM SÄKERHET**:
    // setInsecure() hoppar över valideringen av SSL-certifikatet.
    // Detta är enklast för ett exempel, men mindre säkert för en riktig produkt.
    // För en produktionslösning bör du använda setFingerprint() eller setTrustAnchors().
    client->setInsecure();
 
    // Skapa ett HTTPClient-objekt
    HTTPClient http;
 
    // Bygg URL:en för API-anropet
    String url = "https://api.open-meteo.com/v1/forecast?latitude=52.52&longitude=13.41&current=temperature_2m%22";
 
    Serial.print("Gör HTTP-förfrågan till: ");
    Serial.println(url);
 
    // Starta anslutningen
    if (http.begin(*client, url)) {
      
      // Skicka GET-förfrågan
      int httpCode = http.GET();
 
      if (httpCode > 0) { // Kontrollera om vi fick ett giltigt svar
        
        // HTTP_CODE_OK är 200
        if (httpCode == HTTP_CODE_OK) {
          String payload = http.getString();

         // DynamicJsonDocument doc(1024);  // strukturera om texten till strukturerad format så program kan avläsa
// deserializeJson(doc, payload);

// float temperature = doc["temperature"];
// int humidity = doc["humidity"];
// String status = doc["status"];

// Serial.println(temperature);  // 23.5
// Serial.println(humidity);     // 60
// Serial.println(status);   
          // Serial.println(payload); // Avkommentera för att se hela JSON-svaret
 
          // Tolka JSON-svaret
          // Beräkna en lämplig storlek här: https://arduinojson.org/v6/assistant/
          DynamicJsonDocument doc(1024);
          DeserializationError error = deserializeJson(doc, payload);
 
          if (error) {
            Serial.print("deserializeJson() misslyckades: ");
            Serial.println(error.c_str());
            return;
          }
 
          // Hämta ut de värden vi är intresserade av
          // Strukturen är nu: {"current": {"time": "...", "temperature_2m": 12.3}}
          float temp = doc["current"]["temperature_2m"];
          const char* time = doc["current"]["time"];
 
          // Skriv ut resultatet
          Serial.println("--- Aktuellt väder (Open-Meteo) ---");
          Serial.print("Koordinater: ");
          Serial.print(latitude);
          Serial.print(", ");
          Serial.println(longitude);
          Serial.print("Tid (UTC): ");
          Serial.println(time);
          Serial.print("Temperatur (2m): ");
          Serial.print(temp);
          Serial.println(" °C");
          Serial.println("---------------------------------");
 
        } else {
          Serial.printf("[HTTP] GET... misslyckades, felkod: %d\n", httpCode);
          // Detta händer ofta vid fel API-nyckel (kod 401) eller felstavad stad (kod 404)
        }
      } else {
        Serial.printf("[HTTP] GET... misslyckades, fel: %s\n", http.errorToString(httpCode).c_str());
      }
 
      // Avsluta anslutningen
      http.end();
      
    } else {
      Serial.printf("[HTTP] Kunde inte ansluta\n");
    }
 
  } else {
    Serial.println("WiFi är inte ansluten.");
  }
}
