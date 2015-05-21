/*
	ST7032 I2C LCD control sample
	Original source : HelloWorld.ino (LiquidCrystal Library)
	2013/05/21 tomozh@gmail.com
*/

#include <Wire.h>
#include <ST7032.h>

ST7032 lcd;
const int ledPin =  13;
unsigned long gTime[100];
int gIndex=0;
int prev=1;
int gSony[]={2,1,0,1,1,0,1,0,0,1,0,1,1,1,0,0,0,1,1,1,1};
int gSonyNum=21;


void setup() {
  // set up the LCD's number of columns and rows: 
  lcd.begin(8, 2);
  lcd.setContrast(35);
  // Print a message to the LCD.
  lcd.print("hello, world!");
  

  pinMode(4,OUTPUT);
  pinMode(5,INPUT_PULLUP);
  pinMode(6,INPUT_PULLUP);
  pinMode(7,INPUT_PULLUP);
  pinMode(8,INPUT_PULLUP);
  pinMode(9,INPUT_PULLUP);
  pinMode(10,INPUT_PULLUP);
  pinMode(11,INPUT_PULLUP);
  pinMode(12,INPUT_PULLUP);
  
  Serial.begin(9600);
  
}


void tx(int n)
{
  int k;
  if(n==2)k=90;
  else if(n==1)k=45;
  else if(n==0)k=22;

  for(int i=0;i<k;i++){
    digitalWrite(13,1);
    delayMicroseconds(5);
    digitalWrite(13,0);
    delayMicroseconds(5);
  }
  delayMicroseconds(590);
}

void txsony()
{
  for(int i=0;i<21;i++){
    tx(gSony[i]);
  }
  delay(10);
}


void loop() {

  int now=digitalRead(5);
  if(now!=prev){
    prev=now;
    gTime[gIndex]=micros();
    gIndex++;
    if(gIndex>=99)gIndex=99;
  }
  if(digitalRead(6)==0){
    for(int i=1;i<100;i++){
      Serial.print(i);
      Serial.print(",");
      Serial.print(gTime[i]);
      Serial.print(",");
      Serial.print(gTime[i]-gTime[0]);
      Serial.print(",");
      Serial.print(gTime[i]-gTime[i-1]);
      Serial.write("\r\n");
    }
    gIndex=0;
  }
  if(digitalRead(7)==0)txsony();


/*
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd.print(millis());
  digitalWrite(ledPin, 1);
  delay(10);
  digitalWrite(ledPin, 0);
  delay(40);
  
  char s[9];
  s[0]=digitalRead(5)+'0';
  s[1]=digitalRead(6)+'0';
  s[2]=digitalRead(7)+'0';
  s[3]=digitalRead(8)+'0';
  s[4]=digitalRead(9)+'0';
  s[5]=digitalRead(10)+'0';
  s[6]=digitalRead(11)+'0';
  s[7]=digitalRead(12)+'0';
  s[8]=0;
  
  lcd.setCursor(0, 0);
  // print the number of seconds since reset:
  lcd.print(s);
  */
}

