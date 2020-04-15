//const int Y_pin = 0; // analog pin connected to X output
//const int X_pin = 1; // analog pin connected to Y output

int enableLPin = 3; // pin 1 on L293D IC
int enableRPin = 9; // pin 9 on L293D IC

int motorLPinF = 4; // pin 2 on L293D IC
int motorLPinB = 5; // pin 7 on L293D IC

int motorRPinF = 7; // pin 10 on L293D IC
int motorRPinB = 8; // pin 15 on L293D IC

int motorL = 0;
int motorR = 0;

int xReading = 0;
int yReading = 0;
int xReadingBT = 499;
int yReadingBT = 499;

char c;
String instruction = "";

float v;
float vRaw;
String readData;
int flag = 0;      //makes sure that the serial only prints once the state
int stateStop = 0;
float normalize = 256/363;
int counter = 0;

void setup() {
  // sets the pins as outputs:

  //in the motor pin naming scheme, L is for left, R for right, F for forwards and B for backwards
  pinMode(motorLPinF, OUTPUT);
  pinMode(motorLPinB, OUTPUT);
  
  pinMode(motorRPinF, OUTPUT);
  pinMode(motorRPinB, OUTPUT);

  pinMode(enableLPin, OUTPUT);
  pinMode(enableRPin, OUTPUT);
  
  // initialize serial communication at 38400 bits per second:
  Serial.begin(38400);
}

void loop() {
  //if some date is sent, reads it and saves in state
  flag=0;
  
  while (Serial.available()>0)
  {
    counter++;
    //Serial.println("Hey, you're receiving cereal!!! ");
    c = Serial.read();
    instruction+=c;
    //Serial.print(String(c));  
    if (c!=',' && c!='E')
    {
      readData += c;
    }
    else if (c==',')
    {
      if (readData.toInt() <= 999 and readData.toInt() >= 0)
      {
        xReadingBT = readData.toInt();
      }
      readData = "";
    }
    else if (c=='E')
    {
      //Serial.print('2');
      if (readData.toInt() <= 999 and readData.toInt() >= 0)
      
      {
        yReadingBT = readData.toInt();
      }
      readData="";
      Serial.print(instruction);
      for (int i = 0;  i+instruction.length() < 9; i++)
      {
        Serial.print(" ");
      }
      flag = 1;
      instruction = "";
      break;
    }
    
    
    
  }
  if (flag == 0)
    {
      Serial.print("         ");
    }
  //Serial.flush();



  //xReading and yReading have a range of 0 - 1023, but to understand the code easier I have mapped it to the range -255 - 255
  xReading = map(xReadingBT, 0, 999, -255, 255);
  yReading = -(map(yReadingBT, 0, 999, -255, 255));
  Serial.print("(" + String(xReadingBT) + ", " + String(yReadingBT) + ") ");
 
  //vRaw is the distance of the joystick from the rest position. This is used to determine the speed at which to move the robot (v). 
  v = sqrt(pow(yReading,2) + pow(xReading,2));
  if (v>255)
  {
    v=255;
  }
 
  
  //the maximum value for vRaw is 363 which needs reducing to 255
  //v = map(vRaw, 0, 363, 0, 255);

  //Different steering quadrants
  if (xReading >= 0 && yReading >= 0)
  {
      motorL = v;
      motorR = v - xReading;
  }
  
  else if (xReading < 0 && yReading >= 0)
  {
      motorL = v + xReading;
      motorR = v;
  }
  
  else if (xReading >= 0 && yReading < 0)
  {
      motorL = -v + xReading;
      motorR = -v;
  }
  
  else if (xReading < 0 && yReading < 0)
  {
      motorL = -v;
      motorR = -v -xReading;
  }
  
   

//  motorL = yReading;
//  motorR = yReading;

  

  //the joystick rests slightly off of (0,0), so this means that if it isn't more than 10 away from the centre then the robot should stay at rest
  
  if (v>20)
  {
    //if stateents to determine which pins to set high depending on the speed set to each motor
      if (motorL >= 0)
        {
          digitalWrite(motorLPinF, HIGH);
          digitalWrite(motorLPinB, LOW);
          
        }
        else if (motorL <0)
        {
          digitalWrite(motorLPinF, LOW);
          digitalWrite(motorLPinB, HIGH);
        }
        if (motorR >= 0)
        {
          digitalWrite(motorRPinF, HIGH);
          digitalWrite(motorRPinB, LOW);
          
        }
        else if (motorR <0)
        {
          digitalWrite(motorRPinF, LOW);
          digitalWrite(motorRPinB, HIGH);
        }
        
        if (abs(motorL)>=255)
        {
          motorL = 255* motorL / abs(motorL);
        }
        if (abs(motorR)>=255)
        {
          motorR = 255* motorR / abs(motorR); 
        }
    //if you open the serial monitor, you can see the values of the joystick readings, the speeds written to each motor and the value of v
  
    
        analogWrite(enableLPin, abs(motorL));
        analogWrite(enableRPin, abs(motorR));
  }
  //makes the robot stay at rest if the joystickis at rest 
  else
  {
      digitalWrite(motorLPinF, LOW);
      digitalWrite(motorLPinB, LOW);
      digitalWrite(motorRPinF, LOW);
      digitalWrite(motorRPinB, LOW);
  }

  
  Serial.print("JOYSTICK  ");
  Serial.print(xReading);
  Serial.print(", ");
  Serial.print(yReading);
  Serial.print("  -----  ");

  Serial.print("MOTOR  ");
  Serial.print(motorL);
  Serial.print(", ");
  Serial.print(motorR);
  Serial.print(" | ");
  Serial.print(v);
  Serial.println("");
}
  
