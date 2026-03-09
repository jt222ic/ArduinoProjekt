#include <EEPROM.h>

#define EEPROM_SIZE 128

#define SSID_ADDR 0   // definera användarnamn
#define PASS_ADDR 64  // definera lösenord
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(100);
  Serial.println("\nEEPROM-exempel");

  EEPROM.begin(EEPROM_SIZE);
  String demoSSID = " ";
  String demoPASS = "";

  Serial.println("skriver till eeprom");
  Serial.println(demoSSID);
  Serial.println(demoPASS);

  writeToEeprom(SSID_ADDR, demoSSID);

  EEPROM.commit();

  String ssid = readFromEeprom(SSID_ADDR);
  Serial.println(ssid);  // öpnnar en protokoll och höja en viss minne och committa. pinne till förskrivning.
}

void loop() {
  // put your main code here, to run repeatedly:
}

void writeToEeprom(int addr, const String &msg)  // & och * pointer = pekare
{
  for (int i = 0; i < msg.length(); i++) {
    EEPROM.write(addr + i, msg[i]);
  }
  EEPROM.write(addr + msg.length(), '\0');  // 0 null termometer
}

String readFromEeprom(int addr) {
  String msg = "";
  char ch;
  int i = 0;

  while ((ch = EEPROM.read(addr + i)) != '\0') {
    msg += ch;
    i++;
  }
if(i>EEPROM_SIZE){
  Serial.println("Fel, hittade inte avslutningtecken!");
  return "FEL";
}
  return msg;
}
