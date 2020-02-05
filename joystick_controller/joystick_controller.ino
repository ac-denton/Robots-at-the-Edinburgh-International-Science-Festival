/*
Arduino Robot Car Wireless Control using the HC-05 Bluetooth
       
== MASTER DEVICE - Joystick ==
                       
@author Anthony Campbell
*/

int xAxis, yAxis;
char 'S', 'F', 'R','L', 'B';
int state;

void setup() 
{
  Serial.begin(38400); // Default communication rate of the Bluetooth module
}

void loop()
{
  xAxis = analogRead(A0); // Read Joysticks X-axis
  yAxis = analogRead(A1); // Read Joysticks Y-axis
  
  if (yAxis > 550) //Forward, generally.
  {
    if(xAxis > 470 && xAxis < 550) //Not too far left nor right. X axis is within centered range.
    {
      state = 'F';
      Serial.write(state);
      Serial.println("Forward!);
    }
  }
  else if(xAxis > 550) //Right, generally.
  {
    if(yAxis < 470 && yAxis > 550) //Not too far forward nor backwards. Y axis is within centered range.
    {
      state = 'R';
      Serial.write(state);
      Serial.println("Right!);
    }
  }
  else if(xAxis < 470) //Reverse/Backwards, generally.
  {
    if (yAxis > 470 && yAxis < 550) //Not too far left nor right. X axis is within centered range.
    {
      state = 'B';
      Serial.write(state);
      Serial.println("Forward!);
    }
  }
  else if(xAxis < 470) //Left, generally.
  {
    if(yAxis > 470 & yAxis < 550)//Not too far forward nor bakcwards. Y axis is within centered range.
    {
      state = 'L';
      Serial.write(state);
      Serial.println("Forward!);
    }
  }else
  {
    state = 'S';
    Serial.write(state);
    Serial.println("Stopped...");
  }
  
  // Send the values via the serial port to the slave HC-05 Bluetooth device
  //Serial.write(xAxis/4); // Dividing by 4 for converting from 0 - 1023 to 0 - 256, (1 byte) range
  //Serial.write(yAxis/4);
  Serial.write(xAxis);
  Serial.write(yAxis);
  Serial.println(xAxis);
  Serial.println(yAxis);
  delay(20);
}
