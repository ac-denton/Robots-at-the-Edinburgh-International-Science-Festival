
#include <Servo.h>
Servo myServo;

int reloadDelay = 6500;
int stage = 0;

unsigned long currentMillis;
unsigned long previousMillis = 0;

const int playButton = 2;

int greenGoals = 0;
const int LEDG1 = 3;
const int LEDG2 = 4;
const int LEDG3 = 5;

const int echoPinG = 6;
const int trigPinG = 7;
float durationG;
float distanceG;

int blueGoals = 0;
const int LEDB1 = 8;
const int LEDB2 = 9;
const int LEDB3 = 10;

const int echoPinB = 11;
const int trigPinB = 12;
float durationB;
float distanceB;

bool goalScored = false;

const int posBottom = 178;
const int posTop = 20;
int pos = posBottom;
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
  
  pinMode(playButton, INPUT);
  
  pinMode(LEDG1, OUTPUT);
  pinMode(LEDG2, OUTPUT);
  pinMode(LEDG3, OUTPUT);

  
  pinMode(LEDB1, OUTPUT);
  pinMode(LEDB2, OUTPUT);
  pinMode(LEDB3, OUTPUT);
  
  pinMode(trigPinB, OUTPUT);
  pinMode(echoPinB, INPUT);
  pinMode(trigPinG, OUTPUT);
  pinMode(echoPinG, INPUT);
  delay(4000);
}

void loop() {

   //put your main code here, to run repeatedly:
   resetGame();
   updateGreenGoals();
   updateBlueGoals();
   currentMillis = millis();
  if (currentMillis - previousMillis >= 300) 
  {
    previousMillis = currentMillis;
    stage++;
  }


  if (stage == 0)
  {
    digitalWrite(LEDG1, HIGH);
    digitalWrite(LEDG2, LOW);
    digitalWrite(LEDG3, LOW);
    digitalWrite(LEDB1, HIGH);
    digitalWrite(LEDB2, LOW);
    digitalWrite(LEDB3, LOW);
  }
  else if (stage == 1)
  {
    digitalWrite(LEDG1, LOW);
    digitalWrite(LEDG2, HIGH);
    digitalWrite(LEDB1, LOW);
    digitalWrite(LEDB2, HIGH);
  }
  else if (stage == 2)
  {
    digitalWrite(LEDG2, LOW);
    digitalWrite(LEDG3, HIGH);
    digitalWrite(LEDB2, LOW);
    digitalWrite(LEDB3, HIGH);
  }
  else if (stage == 3)
  { 
    digitalWrite(LEDG3, LOW);
    digitalWrite(LEDG2, HIGH);
    digitalWrite(LEDB3, LOW);
    digitalWrite(LEDB2, HIGH);
  }
  else
  {
    stage = 0;
  }
  
  
  pushStatus = digitalRead(playButton);
  
  if (pushStatus == HIGH)
  {
    gameInProgress = true;
    digitalWrite(LEDG1, HIGH);
    digitalWrite(LEDG2, HIGH);
    digitalWrite(LEDG3, HIGH);
    digitalWrite(LEDB1, HIGH);
    digitalWrite(LEDB2, HIGH);
    digitalWrite(LEDB3, HIGH);
    delay(1000);
    digitalWrite(LEDG1, LOW);
    digitalWrite(LEDB1, LOW);
    delay(1000);
    digitalWrite(LEDG2, LOW);
    digitalWrite(LEDB2, LOW);
    delay(1000);
    digitalWrite(LEDG3, LOW);
    digitalWrite(LEDB3, LOW);
    delay(1000);
    ballReload();
  }
  else
  {
    gameInProgress = false;
  }

  Serial.println(String(pushStatus) + " - " + String(currentMillis) + " - " + String(previousMillis));
  if (gameInProgress == true)
    {
    while (gameInProgress==true)
    {
      pushStatus = digitalRead(playButton);
      if (pushStatus == HIGH)
      {
        gameInProgress = false;
        delay(500);
        break;
      }
      //Ultrasonic sensors code for goal detection
      digitalWrite(trigPinG, LOW);
      delay(2);
      digitalWrite(trigPinG, HIGH);
      delay(10);
      digitalWrite(trigPinG, LOW);
      durationG = pulseIn(echoPinG, HIGH);
      digitalWrite(trigPinB, LOW);
      delay(2);
      digitalWrite(trigPinB, HIGH);
      delay(10);
      digitalWrite(trigPinB, LOW);
      durationB = pulseIn(echoPinB, HIGH);
      
      distanceB = durationB * 0.034/2;
      distanceG = durationG * 0.034/2;
      Serial.println(String(pushStatus) + " " + String(distanceB) + ", " + String(distanceG));
  
      //Statements to change score upon goal and to commence the 
      //sequence that puts the ball back into play
      if ((distanceG <= 5 or distanceG > 15) and distanceG>1)
      {
        greenGoals++;
        updateGreenGoals();
      }
  
      if ((distanceB <= 5 or distanceB > 15) and distanceB>1)
      {
        blueGoals++;
        updateBlueGoals();
      }  
    }
  }
}

//------------------------------------------------------------------- Functions -------------------------------------------------------------------

void updateGreenGoals()
{
  //Updating the scoreboards
  
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
      delay(reloadDelay);
      ballReload();
    }
    else if (greenGoals == 2)
    {
      digitalWrite(LEDG1, HIGH);
      digitalWrite(LEDG2, HIGH);
      digitalWrite(LEDG3, LOW);
      delay(reloadDelay);
      ballReload();
    }
    else if (greenGoals == 3)
    {
      
      greenGoals = 0;
      blueGoals = 0;
      gameInProgress = false;
      i= 0;
      while (i < 5 )
      {
        digitalWrite(LEDB1, LOW);
        digitalWrite(LEDB2, LOW);
        digitalWrite(LEDB3, LOW);
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
}

void updateBlueGoals()
{
    if (blueGoals == 0)
    {
      digitalWrite(LEDB1, LOW);
      digitalWrite(LEDB2, LOW);
      digitalWrite(LEDB3, LOW);
    }
    else if (blueGoals == 1)
    {
      digitalWrite(LEDB1, HIGH);
      digitalWrite(LEDB2, LOW);
      digitalWrite(LEDB3, LOW);
      delay(reloadDelay);
      ballReload();
    }
    else if (blueGoals == 2)
    {
      digitalWrite(LEDB1, HIGH);
      digitalWrite(LEDB2, HIGH);
      digitalWrite(LEDB3, LOW);
      delay(reloadDelay);
      ballReload();
    }
    else if (blueGoals == 3)
    {
      greenGoals = 0;
      blueGoals = 0;
      gameInProgress = false;
      i= 0;
      while (i < 5)
      {
        digitalWrite(LEDG1, LOW);
        digitalWrite(LEDG2, LOW);
        digitalWrite(LEDG3, LOW);
        digitalWrite(LEDB1, HIGH);
        digitalWrite(LEDB2, HIGH);
        digitalWrite(LEDB3, HIGH);
        delay(500);
        digitalWrite(LEDB1, LOW);
        digitalWrite(LEDB2, LOW);
        digitalWrite(LEDB3, LOW);
        delay(500);
        i++;
      }
    }
    else
    {
      while (blueGoals!= 0)
      {
      
        digitalWrite(LEDB1, HIGH);
        digitalWrite(LEDB2, HIGH);
        digitalWrite(LEDB3, HIGH);
        delay(900);
        digitalWrite(LEDB1, LOW);
        digitalWrite(LEDB2, LOW);
        digitalWrite(LEDB3, LOW);
        delay(900);
      }
    }
    
}
void ballReload()
{
  Serial.println(String(distanceB) + ", " + String(distanceG));
  //delay(6500);
  while(pos>posTop)
      {
        pos = pos-1;
        myServo.write(pos);
        delay(8);
      }
      delay(300);
      while(pos<posBottom)
      {
        pos = pos+1;
        myServo.write(pos);
        delay(pos/15);
        if (pos < 100)
        {
          //delay(int(pos/20-5));
        }
        
      }
};
void resetGame()
{
  greenGoals = 0;
  blueGoals = 0;
  
}
