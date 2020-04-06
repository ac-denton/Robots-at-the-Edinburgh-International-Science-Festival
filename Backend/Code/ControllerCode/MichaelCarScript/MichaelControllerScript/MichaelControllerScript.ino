const int Y_pin = 0; // analog pin connected to X output
const int X_pin = 1; // analog pin connected to Y output
int xReading;
int yReading;
String Command;
void setup() {
  Serial.begin(38400); // Default communication rate of the Bluetooth module
}

void loop() {
 delay(30);
 xReading = map(analogRead(X_pin), 0, 1023, 0, 999);
 yReading = map(analogRead(Y_pin), 0, 1023, 0, 999);
 Command = String(xReading) + ',' + String(yReading) + 'E';
 Serial.print(Command); // Sends '1' to serialout
 
}
