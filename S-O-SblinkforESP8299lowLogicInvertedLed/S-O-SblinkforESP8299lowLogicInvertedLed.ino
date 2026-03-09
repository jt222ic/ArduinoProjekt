/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://docs.arduino.cc/hardware/

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  https://docs.arduino.cc/built-in-examples/basics/Blink/
*/
 bool action = false;
// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
 
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  delay(1000);
  Serial.println("setup klar");
}

// the loop function runs over and over again forever
void loop() {

  if(Serial.available()>0)
  {
    
    String cmd = Serial.readStringUntil('\n');
    cmd.trim();

    if(cmd=="start")
     {
      action = true;
      }
      if(cmd =="stop")
      {
        action = false;
      }
  }
// inverted for some reason that LED is on on Low voltage
 // S 
 if(action)
 {
  for(int i=0; i<3; i++){
    digitalWrite(LED_BUILTIN, LOW); // LED ON
    delay(200);                      
    digitalWrite(LED_BUILTIN, HIGH); // LED OFF
    delay(200);
  }
  delay(600); // space between letters

  // O 
  for(int i=0; i<3; i++){
    digitalWrite(LED_BUILTIN, LOW); // LED ON
    delay(600);                      
    digitalWrite(LED_BUILTIN, HIGH); // LED OFF
    delay(200);
  }
  delay(600); // space between letters

  // S 
  for(int i=0; i<3; i++){
    digitalWrite(LED_BUILTIN, LOW); // LED ON
    delay(200);                      
    digitalWrite(LED_BUILTIN, HIGH); // LED OFF
    delay(200);
  }
  delay(2000); // space before repeating SOS
 } 

}
