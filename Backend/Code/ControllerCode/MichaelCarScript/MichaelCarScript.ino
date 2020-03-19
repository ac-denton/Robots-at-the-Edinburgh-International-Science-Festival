const int Y_pin = 0; // analog pin connected to X output
const int X_pin = 1; // analog pin connected to Y output

int enableLPin = 9; // pin 1 on L293D IC
int enableRPin = 3; // pin 9 on L293D IC

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
  pinMode(motorLPinF, OUTPUT);
  pinMode(motorLPinB, OUTPUT);
  
  pinMode(motorRPinF, OUTPUT);
  pinMode(motorRPinB, OUTPUT);

  pinMode(enableLPin, OUTPUT);
  pinMode(enableRPin, OUTPUT);
  // sets enable1Pin and enable2Pin high so that motor can turn on:
  //digitalWrite(enable1Pin, HIGH);
  // digitalWrite(enable2Pin, HIGH);
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
  xReading = analogRead(X_pin);
  xReading = map(xReading, 0, 1023, -255, 255);
  
  yReading = analogRead(Y_pin);
  yReading = map(yReading, 0, 1023, -255, 255);
  
  vRaw = sqrt(pow(yReading,2) + pow(xReading,2));
  //v = 256*vRaw/363;
  v=map(vRaw, 0, 363, 0, 255);

//  if (yReading>=0)
//  {
//    if (xReading>10)
//    {
//      motorL = v;
//      motorR = v-(2*xReading);
//    }
//    else if (xReading<-10)
//    {
//      motorL = v+(2*xReading);
//      motorR = v;
//    }
//  }
//else 
//    {
//      motorL = v;
//      motorR = v;
//    }
  if (xReading >= 0 && yReading >= 0)
      motorL = v;
      motorR = v - 2*xReading;
      
  if (xReading < 0 && yReading >= 0)
      motorL = v + 2*xReading;
      motorR = v;
      
  if (xReading >= 0 && yReading < 0)
      motorL = -v + 2*xReading;
      motorR = -v;
      
  if (xReading < 0 && yReading < 0)
      motorL = -v;
      motorR = -v - 2*xReading;

   

  motorL = -motorL;
  motorR = -motorR;

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
  if (abs(xReading) > 10 or abs(yReading) > 10)
  {
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
    
        analogWrite(enableLPin, abs(motorL));
        analogWrite(enableRPin, abs(motorR));
  }
  else
  {
      digitalWrite(motorLPinF, LOW);
      digitalWrite(motorLPinB, LOW);
      digitalWrite(motorRPinF, LOW);
      digitalWrite(motorRPinB, LOW);
  }
}
  

  //For debugging purpose
  //Serial.println(state);
