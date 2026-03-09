const int buttonPin = 2;     // Button input pin
const int ledPin = 13;       // LED output pin

int buttonState;             
int lastButtonState = LOW;   // Start LOW for pull-down circuit so LOW= 0, HIGH= 1;
int state = 0;               // Tracks button press count (mode)

int AvailableSettings= 2;

void setup() {
  // put your setup code here, to run once:
pinMode(buttonPin,INPUT);         // button taking information
pinMode(ledPin,OUTPUT);                    // output the led light
Serial.begin(9600);  // enable text command or message on serial monitor
}

void loop() {
  // put your main code here, to run repeatedly:
buttonState = digitalRead(buttonPin);  // reading input  HIGH OR LOW

 if (buttonState == HIGH && lastButtonState == LOW) {
    state++;  // avoid multiply true statement when holding a button switch.
    if (state > AvailableSettings)
     {
        state = 0;                          // Wrap around to first state
             
    }                             // Cycle through states
    Serial.print("State: ");
    Serial.println(state);
    delay(200); // simple debounce delay
  }

  lastButtonState = buttonState;  
  switch (state) {                              // switch is more recommended for int datatype
    case 0:
      digitalWrite(ledPin, LOW);
      break;
    case 1:
      digitalWrite(ledPin, HIGH);
      break;
    case 2:
      digitalWrite(ledPin, HIGH);
      delay(100);
      digitalWrite(ledPin, LOW);
      delay(100);
      break;
  }                                    // Update Last button, so the cycle works like this: first cycle non input => lastbutton will also be false during the update
}
