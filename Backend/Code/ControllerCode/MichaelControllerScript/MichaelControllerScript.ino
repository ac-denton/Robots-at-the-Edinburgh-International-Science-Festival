//Bluetooth
#include <SoftwareSerial.h>
SoftwareSerial bluetooth(0,1); //BlueTooth RX ,TX

unsigned long timestampSend = 0; // BT Write wait period
String readString;

void setup()
{
  Serial.begin(9600);
  bluetooth.begin(38400);
  delay(1000);
  Serial.print("Ready");
}

void loop()
{

  if (millis() >= timestampSend + (1000)) // sending data over BT every 500mS
  {
    while (bluetooth.available())
    {
      delay(10);
      char data = bluetooth.read();
      readString += data;

    }

    if (readString.length() > 0) {
      Serial.println("Received Value: " + readString);

      readString = ""; //clears variable for new input
    }

    bluetooth.println("Worked");
    Serial.println("Sent");
    timestampSend = millis();
  }
}
