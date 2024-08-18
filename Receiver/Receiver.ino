//Include Libraries  for reciver
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(9, 8);  
const byte address[6] = "12345";//address of the channel
int m1=6;//connecting M1 pin of motor driver to 6 pin of arduino uno
int m2=10;//connecting M2 pin of motor driver to 10 pin of arduino uno
int m3=5;//connecting M3 pin of motor driver to 5 pin of arduino uno
int m4=3;//connecting M4 pin of motor driver to 3 pin of arduino uno
int val[3];
void setup()
{
 
  Serial.begin(9600);
  pinMode(m1,OUTPUT);
  pinMode(m2,OUTPUT);
  pinMode(m3,OUTPUT);
  pinMode(m4,OUTPUT);
 
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_250KBPS);
  radio.startListening();
}
void Forward()
{
  if(val[0]>125)
  {
    int a=map(val[0],124,255,0,255);
      analogWrite(m1,a);
      analogWrite(m2,0);
      analogWrite(m3,a);
      analogWrite(m4,0);
  }
}
void backward()
{
  if(val[0]<123)
  {
    int b=map(val[0],124,0,0,255);
     analogWrite(m1,0);
      analogWrite(m2,b);
      analogWrite(m3,0);
      analogWrite(m4,b);
  }
}
void left()
{
  if(val[1]<124)
  {
    int a1=map(val[1],124,0,0,255);
    analogWrite(m1,a1);
      analogWrite(m2,0);
      analogWrite(m3,0);
      analogWrite(m4,a1);
  }
}
void Right()
{
   if(val[1]>127)
  {
    int b1=map(val[1],125,255,0,255);
      analogWrite(m1,0);
      analogWrite(m2,b1);
      analogWrite(m3,b1);
      analogWrite(m4,0);
  }
}
void move()
{
 Forward();
 backward();
 left();
 Right();
}
void loop()
{
  if (radio.available())
  {
   radio.read(&val, sizeof(val));
   if((val[0]>=122&&val[0]<=132) && (val[1]>=122&&val[1]<=132)) //stop
    {
      analogWrite(m1,0);
      analogWrite(m2,0);
      analogWrite(m3,0);
      analogWrite(m4,0);
    }
    else
    {
      move();
    }
  }
  else
  {
   
    Serial.println("disConnected");
     analogWrite(m1,0);
      analogWrite(m2,0);
      analogWrite(m3,0);
      analogWrite(m4,0);
  }
}
