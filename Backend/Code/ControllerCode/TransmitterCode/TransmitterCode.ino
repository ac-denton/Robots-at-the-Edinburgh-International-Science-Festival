// SimpleTx - the master or the transmitter

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
//#include <AltSoftSerial.h>

int xAxis, yAxis;
char test[5] = {'S', 'F', 'R','L', 'B'};
char state;
const int X_pin = 1; // analog pin connected to X output
const int Y_pin = 0; // analog pin connected to Y output


#define CE_PIN   9
#define CSN_PIN 10

#define POT_PIN A2

int buttonState = 0;

const byte slaveAddress[5] = {'R','x','A','A','A'};


RF24 radio(CE_PIN, CSN_PIN); // Create a Radio

char dataToSend[10] = "Message 0";
char txNum = '0';


unsigned long currentMillis;
unsigned long prevMillis;
unsigned long txIntervalMillis = 1000; // send once per second


int value;

void setup() {

    Serial.begin(38400);

    Serial.println("SimpleTx Starting");

    radio.begin();
    radio.setDataRate( RF24_250KBPS );
    radio.setRetries(3,5); // delay, count
    radio.openWritingPipe(slaveAddress);
     pinMode(POT_PIN, INPUT);
}

//====================

void loop() {

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
 // Serial.write(state);
  //Serial.println(xAxis);
  //Serial.println(yAxis);
//  delay(100);

updateMessageState(state);

     value = analogRead(POT_PIN);          //Read and save analog value from potentiometer
     value = map(value, 0, 1023, 0, 255); //Map value 0-1023 to 0-255 (PWM)
     if(value < 130)
     {
     send('S');
    }
    else
    {
     send('N');
    }
   // Serial.println(value);
  //  currentMillis = millis();
 //   if (currentMillis - prevMillis >= txIntervalMillis) {
    //    send();
     //   prevMillis = millis();
  //  }
}

//====================

void send(char toSend) {

    bool rslt;
    rslt = radio.write( &dataToSend, sizeof(dataToSend) );
        // Always use sizeof() as it gives the size as the number of bytes.
        // For example if dataToSend was an int sizeof() would correctly return 2

    //Serial.print("Data Sent ");
  //  Serial.print(dataToSend);
    if (rslt) {
      //  Serial.println("  Acknowledge received");
        updateMessage(toSend);
    }
    else {
       // Serial.println("  Tx failed");
    }
}

//================

void updateMessage(char state) {
        // so you can see that new data is being sent
   /* txNum += 1;
    if (txNum > '9') {
        txNum = '0';
    }*/
    dataToSend[8] = state;
}

void updateMessageState(char state) {
        // so you can see that new data is being sent
   /* txNum += 1;
    if (txNum > '9') {
        txNum = '0';
    }*/
    dataToSend[7] = state;
}
