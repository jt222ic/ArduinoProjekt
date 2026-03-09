bool isBlinking = false;
bool isLedOn = false;
 
void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.println("Type 0 in the terminal to show the menu.");
}
 
void loop() {
  if (Serial.available() > 0) {
    String cmd = Serial.readStringUntil('\n');  // read until next row
    cmd.trim();   // trim away blanksteg n or all´
 
    if (cmd == "0") {       // reading the string of 0 not the int o 0
      Serial.println("MENU");
      Serial.println("1. Start blinking");
      Serial.println("2. Stop blinking");
      Serial.println("3. Turn LED ON");
      Serial.println("4. Turn LED OFF");
      Serial.println("5. Show LED status");
    }
    else if (cmd == "1") {
      isBlinking = true;
      Serial.println("Blinking started!");
    }
    else if (cmd == "2") {
      isBlinking = false;
      Serial.println("Blinking stopped!");
    }
    else if (cmd == "3") {
      isLedOn = true;
      digitalWrite(LED_BUILTIN, LOW);
      Serial.println("LED turned ON");
    }
    else if (cmd == "4") {
      isLedOn = false;
      digitalWrite(LED_BUILTIN, HIGH);
      Serial.println("LED turned OFF");
    }
    else if (cmd == "5") {
      if (isBlinking) Serial.println("LED is blinking");
      else if (isLedOn == true) {Serial.println("LED is on");}
      else if (isLedOn == false) {Serial.println("LED is off");}
      else Serial.println("LED is not blinking");
    }
  }
 
  if (isBlinking) {
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
  }
}
