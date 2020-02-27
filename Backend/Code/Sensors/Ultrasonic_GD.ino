const int echoPin= 10;
const int triggerPin= 9;
const int LEDPin= 13;
boolean goal = false;
long signal, inches, centimeters;

void setup() {
Serial.begin(9600);
}

void loop() {
pinMode (echoPin, INPUT);
pinMode (triggerPin, OUTPUT);
pinMode (LEDPin, OUTPUT);

//sends trigger pulse to trigger pin to start sensor into ranging mode
digitalWrite(triggerPin, LOW);
delayMicroseconds(2);
digitalWrite(triggerPin, HIGH);
delayMicroseconds(10);
digitalWrite(triggerPin, LOW);

signal= pulseIn(echoPin, HIGH);

//With the HR-SRO4 sensor, it takes 148 microseconds for a signal to reflect back to the sensor
//this is how we know it's an inch away

inches= signal/148;
centimeters= inches * 2.54; //there are 2.54cm in 1 inch

//the HC-SR04 sensor will check distance to an object every half a second


if (inches <= 3)
{
goal == true;
digitalWrite(LEDPin, HIGH);
Serial.println("GOAAALLL !");
delay(10000);
}
else 
{
  digitalWrite(LEDPin, LOW);
}
}
