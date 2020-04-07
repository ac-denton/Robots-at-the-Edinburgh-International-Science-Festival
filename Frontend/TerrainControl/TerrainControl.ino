
#include <Servo.h>
Servo myServo;
int greenGoals = 0;
int LEDG1 = 3;
int LEDG2 = 4;
int LEDG3 = 5;

int yellowGoals = 0;
int LEDY1 = 6;
int LEDY2 = 7;
int LEDY3 = 8;

bool goalScored = false;

const int pushButton = 12;
int pos = 180;
int i = 0;
bool pushStatus = LOW;
bool pushStatusTemp = LOW;
int ifRead;
bool gameInProgress = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  myServo.attach(13);
  pinMode(pushButton, INPUT);
  myServo.write(pos);
  
  pinMode(A0, INPUT);
  pinMode(LEDG1, OUTPUT);
  pinMode(LEDG2, OUTPUT);
  pinMode(LEDG3, OUTPUT);
  
  pinMode(A1, INPUT);
  pinMode(LEDY1, OUTPUT);
  pinMode(LEDY2, OUTPUT);
  pinMode(LEDY3, OUTPUT);

}

void loop() {

   //put your main code here, to run repeatedly:
//   greenGoals = 0;
//   yellowGoals = 0;
  while (gameInProgress == false)
  {
    digitalWrite(LEDG1, HIGH);
    digitalWrite(LEDG2, LOW);
    digitalWrite(LEDG3, LOW);
    delay(500);
    digitalWrite(LEDG1, HIGH);
    digitalWrite(LEDG2, HIGH);
    digitalWrite(LEDG3, LOW);
    delay(500);
    digitalWrite(LEDG1, HIGH);
    digitalWrite(LEDG2, HIGH);
    digitalWrite(LEDG3, HIGH);
    delay(500);
    digitalWrite(LEDG1, LOW);
    digitalWrite(LEDG2, LOW);
    digitalWrite(LEDG3, LOW);
    delay(500);
  }
  pushStatus = digitalRead(pushButton);
  
  if (pushStatus == HIGH)
  {
    
    gameInProgress = true;
  }
  else
  {
    gameInProgress = false;
  }
  while (gameInProgress==false)
  {
    float GGoal = analogRead(A0);
    float YGoal = analogRead(A1); 
    Serial.println(GGoal);

    if (GGoal <= 10)
    {
      greenGoals++;
      goalScored = true;
    }

    if (YGoal <= 10)
    {
      yellowGoals++;
      goalScored = true;
    }
    
    //Servo code on a timer
    
    if (greenGoals == 0)
    {
      digitalWrite(LEDG1, LOW);
      digitalWrite(LEDG2, LOW);
      digitalWrite(LEDG3, LOW);
    }
    else if (greenGoals == 1)
    {
      digitalWrite(LEDG1, HIGH);
      digitalWrite(LEDG2, LOW);
      digitalWrite(LEDG3, LOW);
    }
    else if (greenGoals == 2)
    {
      digitalWrite(LEDG1, HIGH);
      digitalWrite(LEDG2, HIGH);
      digitalWrite(LEDG3, LOW);
    }
    else if (greenGoals == 3)
    {
      gameInProgress = false;
      i= 0;
      while (i < 10)
      {
        digitalWrite(LEDG1, HIGH);
        digitalWrite(LEDG2, HIGH);
        digitalWrite(LEDG3, HIGH);
        delay(500);
        digitalWrite(LEDG1, LOW);
        digitalWrite(LEDG2, LOW);
        digitalWrite(LEDG3, LOW);
        delay(500);
        i++;
      }
    }
    else
    {
      while (greenGoals!= 0)
      {
        digitalWrite(LEDG1, HIGH);
        digitalWrite(LEDG2, HIGH);
        digitalWrite(LEDG3, HIGH);
        delay(500);
        digitalWrite(LEDG1, LOW);
        digitalWrite(LEDG2, LOW);
        digitalWrite(LEDG3, LOW);
        delay(500);
      }
    }

    if (yellowGoals == 0)
    {
      digitalWrite(LEDY1, LOW);
      digitalWrite(LEDY2, LOW);
      digitalWrite(LEDY3, LOW);
    }
    else if (yellowGoals == 1)
    {
      digitalWrite(LEDY1, HIGH);
      digitalWrite(LEDY2, LOW);
      digitalWrite(LEDY3, LOW);
    }
    else if (yellowGoals == 2)
    {
      digitalWrite(LEDY1, HIGH);
      digitalWrite(LEDY2, HIGH);
      digitalWrite(LEDY3, LOW);
    }
    else if (yellowGoals == 3)
    {
      gameInProgress = false;
      i= 0;
      while (i < 10)
      {
        digitalWrite(LEDY1, HIGH);
        digitalWrite(LEDY2, HIGH);
        digitalWrite(LEDY3, HIGH);
        delay(500);
        digitalWrite(LEDY1, LOW);
        digitalWrite(LEDY2, LOW);
        digitalWrite(LEDY3, LOW);
        delay(500);
        i++;
      }
    }
    else
    {
      while (yellowGoals!= 0)
      {
        digitalWrite(LEDY1, HIGH);
        digitalWrite(LEDY2, HIGH);
        digitalWrite(LEDY3, HIGH);
        delay(900);
        digitalWrite(LEDY1, LOW);
        digitalWrite(LEDY2, LOW);
        digitalWrite(LEDY3, LOW);
        delay(900);
      }
   
    }
    if (goalScored == true)
    {
      ballReload();
      goalScored = false;
    }
    
 
  
    //delay (500);
  //delay(20);
//  if (pos==360)
//  {
//    pos=0;
//    }
  
  }
}
void ballReload()
{
  while(pos>0)
      {
        pos = pos-1;
        myServo.write(pos);
        delay(25);
      }
      delay(500);
      while(pos<180)
      {
        pos = pos+1;
        myServo.write(pos);
        delay(20);
        
      }
};
