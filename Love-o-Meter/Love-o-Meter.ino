
const int sensorPin = A0; // analog pin 0
const float baselineTemp = 20.0;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
 for(int pinNumber = 2; pinNumber<5; pinNumber++)
  {pinMode(pinNumber,OUTPUT);
    digitalWrite(pinNumber,LOW);}
}

void loop() {
  int sensorVal = analogRead(sensorPin); // READ analog to value
  Serial.print("sensor Value: ");
  Serial.print(sensorVal);
  Serial.println("");
  delay(1000);

  float voltage = (sensorVal/1024.0)*5.0; //convert the adc reading to voltage Voltage=1024sensorValue​×5  // sensorvalu är 10 bitar dvs 2^10 =1024, dela upp eller fragmatera med 1024, eftersom arduino kör 5 volt, så referera vi det med att 0,5 *5.
  Serial.print(",Voltage :");
  Serial.print(voltage);
  Serial.println("");
  delay(1000);

  Serial.print(" degree C: ");    // calculating temprature  Vout​=0.5+0.01×T°C​
  float temperature =(voltage - .5)*100;
  Serial.print(temperature);
  Serial.println("");
  delay(1000);

 
 if(temperature < baselineTemp+2)
 {
  digitalWrite(2,LOW);
  digitalWrite(3,LOW);
  digitalWrite(4,LOW);
 }
 else if(temperature >= baselineTemp+2 && (temperature < baselineTemp+4))
 {digitalWrite(2,HIGH);
  digitalWrite(3,LOW);
  digitalWrite(4,LOW);}
  else if(temperature >= baselineTemp+4 && (temperature < baselineTemp+6))
 {digitalWrite(2,HIGH);
  digitalWrite(3,HIGH);
  digitalWrite(4,LOW);}
  else if(temperature >= baselineTemp+6 )
 {digitalWrite(2,HIGH);
  digitalWrite(3,HIGH);
  digitalWrite(4,HIGH);}
  delay(1);
  // put your main code here, to run repeatedly:

}
