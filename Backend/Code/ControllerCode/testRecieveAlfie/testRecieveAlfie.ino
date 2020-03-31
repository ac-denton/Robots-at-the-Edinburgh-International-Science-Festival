String readData;
int counter; 
int flag;
char c='E';
void setup() {
  // put your setup code here, to run once:
  Serial.begin(38400);
}

void loop() {
  flag=0;
  // put your main code here, to run repeatedly:
  counter=0;
  
  if (Serial.available())
  {
    c = Serial.read();
    readData += c;
  }
  if (c=='E')
  {
    Serial.println(readData);
    flag=1;
    readData="";
  }
  
  if (flag=1)
  {
    Serial.println("-------------------------------");
  }
//while (Serial.available() && c!='E') {
//    c = Serial.read();
//    readdata = readdata + c;
//    flag=1;
//    Serial.println(c);
//  }
//  if (flag==1)
//  {
//    Serial.println(readdata);
//    Serial.println("-------------------------------");
//  }
}
