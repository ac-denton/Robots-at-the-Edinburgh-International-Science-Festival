int ifRead;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(A0, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  ifRead = analogRead(A0);

  //Change values depending on the range of the LEDs and your resistance.
  if(analogRead(A0) > 240 && analogRead(A0) < 320)
  {
    Serial.println(ifRead);
    delay(100);
  }
  else
  {
    Serial.println("GOAL!!");
    delay(300);
  }
}
