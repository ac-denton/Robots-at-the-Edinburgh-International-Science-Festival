const int Y_pin = 0; // analog pin connected to X output
const int X_pin = 1; // analog pin connected to Y output

int enableLPin = 3; // pin 1 on L293D IC
int enableRPin = 9; // pin 9 on L293D IC

int motorLPinF = 4; // pin 2 on L293D IC
int motorLPinB = 5; // pin 7 on L293D IC

int motorRPinF = 7; // pin 10 on L293D IC
int motorRPinB = 8; // pin 15 on L293D IC

int motorL = 0;
int motorR = 0;
float xReading = 0;
float yReading = 0;


float v;
float vRaw;
int state;
int flag = 0;      //makes sure that the serial only prints once the state
int stateStop = 0;
float normalize = 256/363;
void setup() {
  // sets the pins as outputs:

  //in the motor pin naming scheme, L is for left, R for right, F for forwards and B for backwards
  pinMode(motorLPinF, OUTPUT);
  pinMode(motorLPinB, OUTPUT);
  
  pinMode(motorRPinF, OUTPUT);
  pinMode(motorRPinB, OUTPUT);

  pinMode(enableLPin, OUTPUT);
  pinMode(enableRPin, OUTPUT);
  
  // initialize serial communication at 9600 bits per second:
  Serial.begin(38400);
}

void loop() {
  //if some date is sent, reads it and saves in state
  if (Serial.available() > 0) {
    state = Serial.read();
    //Serial.print(state);
    flag = 0;
  }

  //xReading and yReading have a range of 0 - 1023, but to understand the code easier I have mapped it to the range -255 - 255
  xReading = map(analogRead(X_pin), 0, 1023, -255, 255);
  yReading = -(map(analogRead(Y_pin), 0, 1023, -255, 255));

  //vRaw is the distance of the joystick from the rest position. This is used to determine the speed at which to move the robot (v). 
  vRaw = sqrt(pow(yReading,2) + pow(xReading,2));
  
  //the maximum value for vRaw is 363 which needs reducing to 255
  v = map(vRaw, 0, 363, 0, 255);

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
      motorL = -v ;
      motorR = -v- xReading;
  }
  
   

//  motorL = yReading;
//  motorR = yReading;

  //if you open the serial monitor, you can see the values of the joystick readings, the speeds written to each motor and the value of v
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
  Serial.print(state);
  
  
  Serial.println("");

  //the joystick rests slightly off of (0,0), so this means that if it isn't more than 10 away from the centre then the robot should stay at rest
  if (abs(motorL) > 10 or abs(motorR) > 10)
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
}
  
