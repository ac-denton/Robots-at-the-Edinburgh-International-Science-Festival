const int Y_pin = 0; // analog pin connected to X output
const int X_pin = 1; // analog pin connected to Y output
int xReading;
int yReading;
String Command;
void setup() {
  Serial.begin(38400); // Default communication rate of the Bluetooth module
}

void loop() {
 xReading = map(analogRead(X_pin), 0, 1023, 0, 999);
 yReading = map(analogRead(Y_pin), 0, 1023, 0, 999);

 String tempX = String(xReading);
 String tempY = String(yReading);
 int strLength = tempX.length();
 char x_array[strLength];
 tempX.toCharArray(x_array, strLength);
 for(int i = 0; i < strLength; i++)
 {
  Serial.write(x_array[i]);
 }

Serial.write(',');

 strLength = tempY.length();
 char y_array[strLength];
 tempY.toCharArray(y_array, strLength);
 for(int i = 0; i < strLength; i++)
 {
  Serial.write(y_array[i]);
 }

 Serial.write('E');
}
