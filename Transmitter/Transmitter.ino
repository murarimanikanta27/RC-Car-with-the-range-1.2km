//Include Libraries   FOR transmitter
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
int x=A0;//connecting x axis pin to A0 of Arduino Uno
int y=A1;//connecting y axis pin to A1 of Arduino Uno


int val[4];
RF24 radio(9, 8);  
const byte address[6] = "12345";//address of the channel
void setup()
{
  Serial.begin(9600);
 
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MAX);// set power level to max
radio.setDataRate(RF24_250KBPS);//set data rate 250kbps for long range 
  radio.stopListening();
}
void loop()
{
   val[0]=analogRead(A0);//reading from A0
   val[1]=analogRead(A1);//reading from A1
   val[0]=map(val[0],0,1023,0,255);//mapping the values of val[0]
   val[1]=map(val[1],0,1023,0,255);//mapping the values of val[1]
   radio.write(&val, sizeof(val));
}
