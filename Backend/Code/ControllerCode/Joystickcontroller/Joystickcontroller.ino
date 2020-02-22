//#include <AltSoftSerial.h>

int xAxis, yAxis;
char test[5] = {'S', 'F', 'R','L', 'B'};
char state;
const int X_pin = 1; // analog pin connected to X output
const int Y_pin = 0; // analog pin connected to Y output

//AltSoftSerial BTserial(8, 9); // RX | TX 

void setup() 
{
  Serial.begin(38400); // Default communication rate of the Bluetooth module
  //BTserial.begin(38400);
}

void loop()
{
  xAxis = analogRead(X_pin); // Read Joysticks X-axis
  yAxis = analogRead(Y_pin); // Read Joysticks Y-axis
  
  if (yAxis > 550) //Forward, generally.
  {
    if(xAxis > 470 && xAxis < 550) //Not too far left nor right. X axis is within centered range.
    {
      state = 'F';
    /*  Serial.print("Forward");
       Serial.print("X-axis: ");
  Serial.print(analogRead(X_pin));
  Serial.print("\n");
  Serial.print("Y-axis: ");
  Serial.println(analogRead(Y_pin));
  Serial.print("\n\n");*/
    }
  }
  else if(xAxis > 550) //Right, generally.
  {
   // if(yAxis < 470 && yAxis > 550) //Not too far forward nor backwards. Y axis is within centered range.
    //{
      state = 'R';
    /*  Serial.println("Right!");
        Serial.print("X-axis: ");
  Serial.print(analogRead(X_pin));
  Serial.print("\n");
  Serial.print("Y-axis: ");
  Serial.println(analogRead(Y_pin));
  Serial.print("\n\n");*/
  //  }
  }
  else if(yAxis < 470) //Reverse/Backwards, generally.
  {
    //if (yAxis > 470 && yAxis < 550) //Not too far left nor right. X axis is within centered range.
    //{
      state = 'B';
    /*  Serial.println("Back!");
        Serial.print("X-axis: ");
  Serial.print(analogRead(X_pin));
  Serial.print("\n");
  Serial.print("Y-axis: ");
  Serial.println(analogRead(Y_pin));
  Serial.print("\n\n");*/
    //}
  }
  else if(xAxis < 470) //Left, generally.
  {
  //  if(yAxis > 470 & yAxis < 550)//Not too far forward nor bakcwards. Y axis is within centered range.
    //{
      state = 'L';
    /*  Serial.println("Left!");
       Serial.print("X-axis: ");
  Serial.print(analogRead(X_pin));
  Serial.print("\n");
  Serial.print("Y-axis: ");
  Serial.println(analogRead(Y_pin));
  Serial.print("\n\n");*/
    //}
  }
  else if(xAxis < 600 && xAxis > 400 && yAxis < 600 && xAxis > 400)
  {
    state = 'S';
  /*  Serial.println("Stopped...");
      Serial.print("X-axis: ");
  Serial.print(analogRead(X_pin));
  Serial.print("\n");
  Serial.print("Y-axis: ");
  Serial.println(analogRead(Y_pin));
  Serial.print("\n\n");*/
  }
  
  // Send the values via the serial port to the slave HC-05 Bluetooth device
  //Serial.write(xAxis/4); // Dividing by 4 for converting from 0 - 1023 to 0 - 256, (1 byte) range
  //Serial.write(yAxis/4);
  //Serial.write(xAxis);
  //Serial.write(yAxis);
  Serial.write(state);
  //Serial.println(xAxis);
  //Serial.println(yAxis);
  delay(20);
}
