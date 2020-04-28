//MasterAddress: 98d3:37:ae65
char c;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(38400);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()>0)
  {
    c = Serial.read();
    //Serial.println(c);
  }
  Serial.println(c);
}
