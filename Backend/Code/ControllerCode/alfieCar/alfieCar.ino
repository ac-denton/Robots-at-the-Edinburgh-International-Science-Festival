#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN   9
#define CSN_PIN 10

int enable1Pin = 3; // pin 1 on L293D IC
int enable2Pin = 6; // pin 9 on L293D IC

int motor1Pin1 = 5; // pin 2 on L293D IC
int motor1Pin2 = 6; // pin 7 on L293D IC

int motor2Pin1 = 7; // pin 10 on L293D IC
int motor2Pin2 = 8; // pin 15 on L293D IC

char state;
int flag = 0;      //makes sure that the serial only prints once the stat
int carSpeed;

int curTime;
int delayTime;
// SimpleRx - the slave or the receiver

bool isStunned = false;


const byte thisSlaveAddress[5] = {'R','x','A','A','A'};

RF24 radio(CE_PIN, CSN_PIN);

char dataReceived[10]; // this must match dataToSend in the TX
bool newData = false;



void setup() {
  // sets the pins as outputs:
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
 pinMode(enable1Pin, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(enable2Pin, OUTPUT);
 // analogWrite(enable1Pin, 255);
 // analogWrite(enable2Pin, 255);
  Serial.begin(38400);
 Serial.println("SimpleRx Starting");
    radio.begin();
    radio.setDataRate( RF24_250KBPS );
    radio.openReadingPipe(1, thisSlaveAddress);
    radio.startListening();
}

void loop() {

  getData();
   showData();
  
  //if some date is sent, reads it and saves in state
  if (Serial.available() > 0) {
   state = Serial.read();
    Serial.print(state);
    flag = 0;
  }
  if(isStunned)
  {
  //  Serial.println("Stunned!");
  }
  else
  {
 //   Serial.println("not stunnned :(");
  }
if(isStunned == true)
{
  //Serial.println("delaytime equal to: " + delayTime);
  if(millis() > delayTime)
  {
    freeCar();
  }
}
if(dataReceived[8] == 'S' && isStunned == false)
{
  stunCar();
  curTime = millis();
  delayTime = curTime + 2000;
}
//else if(dataReceived[8] == 'N' && isStunned == false)
//{
//  Serial.println("in check state loop");
  analogWrite(enable1Pin, 255);
  analogWrite(enable2Pin, 255);
  // if the state is 'F' the DC motor will go forward
  if (state == 'F') {
    digitalWrite(motor1Pin1, LOW);
      digitalWrite(motor1Pin2, HIGH);
    digitalWrite(motor2Pin1, LOW);
   digitalWrite(motor2Pin2, HIGH);
    if (flag == 0) {
  //    Serial.println("Go Forward!");
      flag = 1;
    }
  }

  // if the state is 'L' the motor will turn left
  else if (state == 'L') {
    digitalWrite(motor1Pin1, HIGH);
    digitalWrite(motor1Pin2, LOW);
    digitalWrite(motor2Pin1, LOW);
    digitalWrite(motor2Pin2, HIGH);
    if (flag == 0) {
  //    Serial.println("Turn LEFT");
      flag = 1;
    }
  }
  // if the state is 'S' the motor will Stop
  else if (state == 'S') {
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, LOW);
    digitalWrite(motor2Pin1, LOW);
    digitalWrite(motor2Pin2, LOW);
    if (flag == 0) {
    //  Serial.println("STOP!");
      flag = 1;
    }
  }
  // if the state is 'R' the motor will turn right
  else if (state == 'R') {
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, HIGH);
    digitalWrite(motor2Pin1, HIGH);
    digitalWrite(motor2Pin2, LOW);
      flag = 1;
    }
  // if the state is 'B' the motor will Reverse
  else if (state == 'B') {
    digitalWrite(motor1Pin1, HIGH);
    digitalWrite(motor1Pin2, LOW);
    digitalWrite(motor2Pin1, HIGH);
    digitalWrite(motor2Pin2, LOW);
    if (flag == 0) {
     // Serial.println("Reverse!");
      flag = 1;
    }
  }
}

void getData() {
    if ( radio.available() ) {
        radio.read( &dataReceived, sizeof(dataReceived) );
       // Serial.println("in get data");
       state = dataReceived[7];
       int n = dataReceived[3];
       char ints[n];
       for(int i = 0; i < n; i++)
       {
        ints[i] = dataReceived[i];
       }
       carSpeed = atoi(ints); 
       Serial.println(carSpeed);
        newData = true;
    }
}

void showData() {
    if (newData == true) {

        newData = false;
    }
}

void stunCar()
{
  isStunned = true;
  analogWrite(enable1Pin, 0);
  analogWrite(enable2Pin, 0); 
}

void freeCar()
{
  isStunned = false;
}

void changeRighttWheelSpeed(int value)
{
  analogWrite(enable1Pin, value);
}

void changeLeftWheelSpeed(int value)
{
  analogWrite(enable2Pin, value);
}
