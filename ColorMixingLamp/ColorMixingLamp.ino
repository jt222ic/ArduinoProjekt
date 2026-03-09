//Arduino uno

const int greenLedPin=9;
const int redLedPin = 10;
const int blueLedPin = 11;

const int redSensorPin = A0;
const int greenSensorPin = A1;
const int blueSensorPin = A2;

int redValue = 0;
int greenValue = 0;
int blueValue = 0;

int redSensorValue = 0;
int greenSensorValue = 0;
int blueSensorValue = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(greenLedPin,OUTPUT);   // digital Pin output
  pinMode(redLedPin, OUTPUT);
  pinMode(blueLedPin,OUTPUT);

  // pinMode(redSensorPin,INPUT);   // Analog Pin Input
  // pinMode(greenSensorPin, INPUT);
  // pinMode(blueSensorPin,INPUT);



}

void loop() {
  // put your main code here, to run repeatedly:

redSensorValue = analogRead(redSensorPin);  // translate reading to value
greenSensorValue = analogRead(greenSensorPin);
blueSensorValue = analogRead(blueSensorPin);


Serial.print("Raw Sensor Values \t red: ");
Serial.print(redSensorValue);
Serial.print("\t green: ");
Serial.print(greenSensorValue);
Serial.print("\t blue: ");
Serial.print(blueSensorValue);

redValue= redSensorValue/4;    // scale down from 1023 = 10bit to 256 = 8 bit by divided by 4
greenValue =greenSensorValue/4;  // because analog read is expected 256 to read and write in PWM.
blueValue = blueSensorValue/4;

// Serial.print("Mapped Sensor Values \t red: ");
// Serial.print(redValue);
// Serial.print("\t green: ");
// Serial.print(greenValue);
// Serial.print("\t blue: ");
// Serial.print(blueValue);

analogWrite(redLedPin,redValue);
analogWrite(greenLedPin,greenValue);
analogWrite(blueLedPin,blueValue);


}
