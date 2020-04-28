

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

//Default values in case of communication failure so the car remins stationary
int xReadingBT = 499;
int yReadingBT = 499;

//Character used to temporarily store value sent over bluetooth
char c;
//Used to store entire instructions for the car
String instruction = "";
//Temporarily store parts of the instructions of the car
String readData;

//Magnitude of velocity the car should have 
float v;

int flag = 0;      //makes sure that the serial only prints once the state
int stateStop = 0;
int counter = 0;

void setup() {

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
    //Reading the character sent by the controller
    c = Serial.read();
    //building the instruction as it receives characters
    instruction+=c;
    //Determines whether the character is a separator. if it isn't then it must be part of a reading
    if (c!=',' && c!='E')
    {
      readData += c;
    }
    //Used to separate readings. Once it encounters this character it knows that the first reading is received
    else if (c==',')
    {
      //if statement used to ignore any values that don't fall within the range of 0-999
      if (readData.toInt() <= 999 and readData.toInt() >= 0)
      {
        xReadingBT = readData.toInt();
      }
      //wipes readData so that it is ready to receive the second reading
      readData = "";
    }
    //the E character is used to denote the end of an instruction. This means the secod reading is received and useable
    else if (c=='E')
    {
      if (readData.toInt() <= 999 and readData.toInt() >= 0)
      {
        yReadingBT = readData.toInt();
      }
      readData="";
      //Used for 
      for (int i = 0;  i+instruction.length() < 9; i++)
      {
        //Serial.print(" ");
      }
      //alerts the program that an instruction was successfully received
      flag = 1;
      //wipes instruction, ready for the next one 
      instruction = "";
      break;
    }
    
    
    
  }
  if (flag == 0)
    {
      //Serial.print("         ");
    }



  //xReading and yReading have a range of 0 - 1023, but to understand the code easier I have mapped it to the range -255 - 255
  xReading = map(xReadingBT, 0, 999, -255, 255);
  yReading = -(map(yReadingBT, 0, 999, -255, 255));
  //Serial.print("(" + String(xReadingBT) + ", " + String(yReadingBT) + ") ");
 
  //vRaw is the distance of the joystick from the rest position. This is used to determine the speed at which to move the robot (v). 
  v = sqrt(pow(yReading,2) + pow(xReading,2));
  if (v>255)
  {
    v=255;
  }
 
  
//  //Different steering quadrants for the joystick
//  if (xReading >= 0 && yReading >= 0)
//  {
//      motorL = v;
//      motorR = v - xReading;
//  }
//  
//  else if (xReading < 0 && yReading >= 0)
//  {
//      motorL = v + xReading;
//      motorR = v;
//  }
//  
//  else if (xReading >= 0 && yReading < 0)
//  {
//      motorL = -v + xReading;
//      motorR = -v;
//  }
//  
//  else if (xReading < 0 && yReading < 0)
//  {
//      motorL = -v;
//      motorR = -v -xReading;
//  }

    //Different steering quadrants for the joystick

    //Top quadrant
  if (yReading >= xReading && yReading >= -xReading)
  {
    Serial.print("T ");
      motorL = v;
      motorR = v;
  }
  //Bottom quadrant
  else if (yReading < xReading && yReading < -xReading)
  {
    Serial.print("B ");
      motorL = -v;
      motorR = -v;
  }
  //Left quadrant
  else if (yReading <= -xReading && yReading >= xReading)
  {
    Serial.print("L ");
      motorL = -v;
      motorR = v;
  }
  //Right quadrant
  else if (yReading > -xReading && yReading < xReading)
  {
    Serial.print("R ");
      motorL = v;
      motorR = -v;
  }
  

  //the joystick rests slightly off of (0,0), so this means that if it isn't more
  //than 10 away from the centre then the robot should stay at rest
  
  if (v>50)
  {
    //if statements to determine which pins to set 
    //high depending on the speed set to each motor
      motorL = -motorL;
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

        //used to cap the motor speed and direction between the ranges of -255 and 255
//        if (abs(motorL)>=255)
//        {
//          motorL = 255 * motorL / abs(motorL);
//        }
//        if (abs(motorR)>=255)
//        {
//          motorR = 255 * motorR / abs(motorR); 
//        }

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
      motorL = 0;
      motorR = 0;
  }
  

  //Used to monitor what the controller is sending vs what the car is receiving and doing
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
  
