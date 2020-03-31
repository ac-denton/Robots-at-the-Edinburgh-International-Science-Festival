String readData;
int counter; 
int flag;
String xReading;
String yReading;
char c='E';
void setup() {
  // put your setup code here, to run once:
  Serial.begin(38400);
}

void loop() {
  
  // put your main code here, to run repeatedly:
  
  counter=0;
  flag=0;
  
  if (Serial.available())
  {
    c = Serial.read();
    //Serial.println(c);
  }

  if (c!=',' && c!='E')
  {
    readData += c;
  }
  else if (c==',')
  {
    xReading = readData;
    //readData = "";
  }
  else if (c=='E')
  {
    yReading = readData;
    //readData="";
    flag=1;
  }
  
  if (flag==1)
  {
    Serial.println(readData);
    Serial.println("----------------------");
    readData="";
  }
}
