
int buttons[6];


int notes[] = {262,294,330,349};
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
buttons[0] = 2;
}

void loop() {
  // put your main code here, to run repeatedly:


int keyVal = analogRead(A0);
Serial.println(keyVal);

if(keyVal==1024)
{
  tone(8,notes[0]);
}
else if(keyVal >=70 && keyVal <=120)
{
  tone(8,notes[1]);
}
else
{
  noTone(8);
}
}
