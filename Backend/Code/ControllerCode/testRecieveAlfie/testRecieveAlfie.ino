String readdata;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(38400);
}

void loop() {
  // put your main code here, to run repeatedly:
while (Serial.available()) {
    delay(10);
    char c = Serialerial.read();
    readdata += c;
  }
  Serial.println(readdata);
}
