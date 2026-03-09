const int analogPin = A0;
const float referenceVoltage = 3.3;
const int resolution = 1023;   // 10-bit ADC (0–1023)


int rawOffset = 0;             // Offset value (calibration)

void setup()
{
 Serial.begin(9600);

  // --- Offset calibration (run once at startup) ---
  long offsetSum = 0;

  for (int i = 0; i < 100; i++) {
    offsetSum += analogRead(analogPin);
    delayMicroseconds(200);
  }

  rawOffset = offsetSum / 100;   // Average offset value

}
void loop() {

  // --- Take 100 samples and calculate average ---
  long sum = 0;

  for (int i = 0; i < 100; i++) {
    sum += analogRead(analogPin);
    delayMicroseconds(200);
  }

  float rawAverage = sum / 100.0;

  // --- Remove offset ---
  float correctedRaw = rawAverage - rawOffset;

  if (correctedRaw < 0) {
    correctedRaw = 0;
  }

  // --- Convert to voltage ---
  float voltage = correctedRaw * (referenceVoltage / resolution);

  // Print result
  Serial.print("Voltage: ");
  Serial.println(voltage, 4);

  //resistance result

  float resistance = measureResistance();
  Serial.print("Resostamce Ohms: ");
  Serial.println(resistance);
  

  delay(500);
}

float measureResistance() {
  const float Vcc = 5.0;
  const float Rknown = 1000.0;

  int raw = analogRead(A0);
  float Vout = raw * (Vcc / 1023.0);

  float Runknown = Rknown * (Vout / (Vcc - Vout));

  return Runknown;
}