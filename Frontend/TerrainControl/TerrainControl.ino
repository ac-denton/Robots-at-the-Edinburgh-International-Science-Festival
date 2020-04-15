
#include <Servo.h>
Servo myServo;

const int playButton = 2;

int greenGoals = 0;
const int LEDG1 = 3;
const int LEDG2 = 4;
const int LEDG3 = 5;

const int echoPinG = 6;
const int trigPinG = 7;
float durationG;
float distanceG;

int yellowGoals = 0;
const int LEDY1 = 8;
const int LEDY2 = 9;
const int LEDY3 = 10;

const int echoPinY = 11;
const int trigPinY = 12;
float durationY;
float distanceY;

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
  myServo.write(pos);
  
  pinMode(pushButton, INPUT);
  
  pinMode(LEDG1, OUTPUT);
  pinMode(LEDG2, OUTPUT);
  pinMode(LEDG3, OUTPUT);

  
  pinMode(LEDY1, OUTPUT);
  pinMode(LEDY2, OUTPUT);
  pinMode(LEDY3, OUTPUT);
  
  pinMode(trigPinY, OUTPUT);
  pinMode(echoPinY, INPUT);
  

}

void loop() {

   //put your main code here, to run repeatedly:
//   greenGoals = 0;
//   yellowGoals = 0;
//  while (gameInProgress == false)
//  {
//    digitalWrite(LEDG1, HIGH);
//    digitalWrite(LEDG2, LOW);
//    digitalWrite(LEDG3, LOW);
//    delay(500);
//    digitalWrite(LEDG1, HIGH);
//    digitalWrite(LEDG2, HIGH);
//    digitalWrite(LEDG3, LOW);
//    delay(500);
//    digitalWrite(LEDG1, HIGH);
//    digitalWrite(LEDG2, HIGH);
//    digitalWrite(LEDG3, HIGH);
//    delay(500);
//    digitalWrite(LEDG1, LOW);
//    digitalWrite(LEDG2, LOW);
//    digitalWrite(LEDG3, LOW);
//    delay(500);
//  }


  
  pushStatus = digitalRead(pushButton);
  
  if (pushStatus == HIGH)
  {
    
    gameInProgress = true;
  }
  else
  {
    gameInProgress = false;
  }
  while (gameInProgress==true)
  {
    
    digitalWrite(trigPinY, LOW);
    digitalWrite(trigPinG, LOW);
    delay(2);
    digitalWrite(trigPinY, HIGH);
    digitalWrite(trigPinG, HIGH);
    delay(10);
    digitalWrite(trigPinY, LOW);
    digitalWrite(trigPinG, LOW);
  
    durationY = pulseIn(echoPinY, HIGH);
    durationG = pulseIn(echoPinG, HIGH);
    distanceY = durationY * 0.034/2;
    distanceG = durationG * 0.034/2;
    Serial.println(String(distanceY) + ", " + String(distanceG));

    if (distanceG <= 10)
    {
      greenGoals++;
      ballReload();

//      digitalWrite(LEDG1, HIGH);
//      delay(500);
//      digitalWrite(LEDG1, LOW);
//      delay(500);
//      digitalWrite(LEDG1, HIGH);
//      delay(500);
//      digitalWrite(LEDG1, LOW);
//      delay(500);
//      digitalWrite(LEDG1, HIGH);

    }

    if (distanceY <= 10)
    {
      yellowGoals++;
      ballReload();
    }
    
    
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
      greenGoals = 0; 
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
        delay(200);
        digitalWrite(LEDG1, LOW);
        digitalWrite(LEDG2, LOW);
        digitalWrite(LEDG3, LOW);
        delay(200);
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
      yellowGoals = 0;
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
  delay(6000);
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
