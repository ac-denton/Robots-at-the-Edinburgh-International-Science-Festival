
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

int xAxis, yAxis;
char test[5] = {'R','x','A','A','A'};
char state;
const int X_pin = 1; // analog pin connected to X output
const int Y_pin = 0; // analog pin connected to Y output


#define CE_PIN   9
#define CSN_PIN 10

#define POT_PIN A2

int buttonState = 0;

const byte slaveAddress[5] = {'R','x','A','A','A'};


RF24 radio(CE_PIN, CSN_PIN); // Create a Radio

char dataToSend[10] = "AAAAAAAAA";
char txNum = '0';

int value;
char char3[3];
char char2[2];
char char1[1];
String strVal;
String strXVal;
String strYVal;

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

 // xAxis += 10000;
  
  if (yAxis > 550) //Forward, generally.
  {
    if(xAxis > 470 && xAxis < 550) //Not too far left nor right. X axis is within centered range.
    {
      state = 'F';
    }
  }
  else if(xAxis > 550) //Right, generally.
  {
      state = 'R';
  }
  else if(yAxis < 470) //Reverse/Backwards, generally.
  {
      state = 'B';
  }
  else if(xAxis < 470) //Left, generally.
  {
      state = 'L';
  }
  else if(xAxis < 600 && xAxis > 400 && yAxis < 600 && xAxis > 400)
  {
    state = 'S';
  }

  Serial.write(state);
  //delay(10);

//Serial.println(xAxis);
//Serial.println(yAxis);
/*strXVal = xAxis;
strYVal = yAxis;

char strchX[strXVal.length()];
strXVal.toCharArray(strchX, strXVal.length());

  Serial.write(strchX);

  char strchY[strYVal.length()];
  strYVal.toCharArray(strchY, strYVal.length());
  
  Serial.write(strchY);*/

//updateMessageState(state);

     value = analogRead(POT_PIN);          //Read and save analog value from potentiometer
     value = map(value, 0, 1023, 0, 255); //Map value 0-1023 to 0-255 (PWM)
   //  Serial.println(value);
     strVal = String(value);
     if(value >= 100)
     {
    strVal.toCharArray(char3, 3);
     }
     else if(value < 100 && value >= 10)
     {
      strVal.toCharArray(char2, 2);
     }
     else
     {
      strVal.toCharArray(char1, 1);
     }

   // Serial.println(strVal.length());

   for(int i = 0; i < strVal.length(); i++)
    {
      dataToSend[i] = strVal[i];
     // Serial.println(dataToSend[i]);
    }
    //Serial.print(dataToSend[0]);
    //Serial.print(dataToSend[1]);
    //Serial.print(dataToSend[2]);
    dataToSend[3] = strVal.length();
     
    send();
}

void send() {
   
    
    bool rslt;
    rslt = radio.write( &dataToSend, sizeof(dataToSend) );
       
        // Always use sizeof() as it gives the size as the number of bytes.
       
        // For example if dataToSend was an int sizeof() would correctly return 

    if (rslt) {
     //   updateMessage(toSend);
    }
    else {
       // Serial.println("  Tx failed");
    }
}

//================

void updateMessage(char state)
{
    dataToSend[8] = state;
}

void updateMessageForChar()
{
    for(int i = 0; i < strVal.length(); i++)
    {
      dataToSend[i] = strVal[i];
     // Serial.println(dataToSend[i]);
    }
    Serial.println(dataToSend[0]);
     Serial.println(dataToSend[1]);
      Serial.println(dataToSend[2]);
    dataToSend[3] = strVal.length();
}
