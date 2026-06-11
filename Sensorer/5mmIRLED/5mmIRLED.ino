// Pulse Monitor Test Script
int sensorPin = 4;   // A2 pin
int irLedPin = 3; 
double alpha = 0.75;
int period = 100;
double change = 0.0;
double minval = 0.0;
void setup ()
{
   pinMode(irLedPin, OUTPUT);
   pinMode(sensorPin, INPUT);  
   //digitalWrite(irLedPin, HIGH);
  Serial.begin (9600);
}
void loop ()
{
    static double oldValue = 0;                         // IMPORTANT have correct pin , the receiver have a red led to indicate if it detects ir led
    static double oldChange = 0;                       // it will have pulsating blinking,   the other problem is the digital read is too slow or 2 fast
  // generate 38 kHz signal on pin 3 for 1 second
  tone(irLedPin, 38000);  
  delay(1000);
  noTone(irLedPin);         // stop for 1 second
  delay(1000);
  
  int rawValue = digitalRead (sensorPin);
   
    double value = alpha * oldValue + (1 - alpha) * rawValue;      // Apply exponential moving average (low-pass filter) to smooth the sensor readings
// 'alpha' controls smoothing: higher alpha = smoother but slower response
// Combines previous filtered value (oldValue) with new raw reading (rawValue)
// y[n]=αy[n−1]+(1−α)x[n]  Low pass filter d.v.s alpha *oldvalue = y * n-1,  1- alpha  * rå data   alpha role = adjusting  so högre alpha = smoother , lägre alpha = faster response
    
    Serial.print("Raw: ");
    Serial.print (rawValue);
    Serial.print (" IR LED: ");
    Serial.print(irLedPin);
    Serial.print (",");
     Serial.print("Filtered: ");
    Serial.println (value);
    oldValue = value;
 
    delay (period);
}
