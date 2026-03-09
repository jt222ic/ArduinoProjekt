
//Mood cue update with additional button switch

#include <Servo.h>

Servo myServo;


int potVal;
int angle;

void setup() {
  
  pinMode(8,INPUT);
  pinMode(7,INPUT);
  myServo.attach(9);            // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
bool switchstate = digitalRead(8);
bool secondswitchstate = digitalRead(7);

 if (switchstate == LOW) {
    angle--;
     if (angle < 0) angle = 0;
    myServo.write(angle);
    delay(15);  // smooth movement
  }

  // If RIGHT button pressed → rotate right
  if (secondswitchstate == LOW) {
    angle++;
    if (angle > 180) angle = 180;
    myServo.write(angle);
    delay(15);  // smooth movement
  }
// Serial.print("switchstate: ");
// Serial.println(switchstate);
// delay(1000);
// Serial.println("");
// Serial.print("secondswitchstate: ");
// Serial.println(secondswitchstate);
// delay(1000);
 //potVal = analogRead(potPin);
//  Serial.println("switchstate: ");
//  Serial.print(switchstate);

//  angle = map(potVal,0,1023,0,179);
//  Serial.print(", angle: ");
//  Serial.print(angle);

//  myServo.write(angle);
 delay(15);
}
