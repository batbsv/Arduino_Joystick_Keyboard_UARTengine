// modified library by BAT_bsv
// Program used to test the USB Joystick library when used as 
// a Flight Controller on the Arduino Leonardo or Arduino 
// Micro.
//https://github.com/MHeironimus/ArduinoJoystickLibrary/tree/version-1.0
// Matthew Heironimus
// 2016-05-29 - Original Version
//------------------------------------------------------------
// modified library by BAT_bsv


#define bit16 65535
#define bit15 32767
#define bit14 16383
#define bit13 8192
#define bit12 4095
#define bit11 2047
#define bit10 1023
#define bit9 511
#define bit8 255

//#include <Mouse.h>
#include <Keyboard.h>
#include <Joystick.h>

int axisState [8] ={0,0,0,0,0,0,0,0};
int UARTaxis  [8]= {0,0,0,0,0,0,0,0};
int UARTaxiss  [8]= {1023,1023,1023,1023,1023,1023,1023,1023};
char UARTindex=0;

//analog raw variable
int axAxis;
int ayAxis;
int azAxis;
int arxAxis;
int aryAxis;
int arzAxis;
int aslider1;
int aslider2;

int temp;
int test=0;
unsigned long time;
unsigned long startime;
Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, 
  JOYSTICK_TYPE_JOYSTICK, 128, 2,
  true, //X
  true, //Y
  true, //Z
  true, //rX
  true, //rY
  true, //rZ
  true, //Slider 1
  true  //Slider 2
  );

//const bool testAutoSendMode = true;
const bool testAutoSendMode = false;
//select send mode for joystick, auto or manual 
int incomingByte = 0;

void setup() {
  Serial.begin (115200); 
 Serial1.begin(115200);
 Serial.setTimeout(1);
  Keyboard.begin(); 
  
//setup axis range hard
  Joystick.setXAxisRange(-bit15,bit15);
  Joystick.setYAxisRange(-bit15, bit15);
  Joystick.setZAxisRange(-bit9, bit9);
  Joystick.setRxAxisRange(-bit9, bit9);
  Joystick.setRyAxisRange(-bit9, bit9);
  Joystick.setRzAxisRange(-bit9, bit9);
  Joystick.setSlider1Range(-bit9, bit9);
  Joystick.setSlider2Range(-bit9, bit9); 

//Joystick.setHatSwitch(0, JOYSTICK_HATSWITCH_RELEASE);
//Joystick.setHatSwitch(1, JOYSTICK_HATSWITCH_RELEASE);

  if (testAutoSendMode)
  {
    Joystick.begin();
  }
  else
  {
    Joystick.begin(false);
  }
}

void loop() {
    
   axAxis =analogRead (A0);
   ayAxis =axAxis;//analogRead (A1);
   azAxis =axAxis;//analogRead (A2);
   arxAxis =axAxis;//analogRead (A3);
   aryAxis =axAxis;//analogRead (A4);
   arzAxis =axAxis;//analogRead (A5);      
   aslider1=axAxis;//analogRead (A6);
   aslider2=axAxis;//analogRead (A7);

//8 осей
//x,y,z, rx, ry, rz, s1, s2 
//a,b,c,  d,  e,  f,  g,  h
startime = micros();
//start UART engine
//while 
if (Serial.available()>0){
  Serial.println(time);
  incomingByte = Serial.read();
  if(incomingByte =='A')
  {
incomingByte = Serial.read();
Serial.write(incomingByte);
switch (incomingByte)
  {
    case  'a':  
    UARTaxis  [0]= parseS();
    UARTindex=1;
    break;
    case  'b':
    UARTaxis  [1]=parseS();
    UARTindex=2;
    break;
    case  'c':
    UARTaxis  [2]=parseS();
    UARTindex=3;
    break;
    case  'd':
    UARTaxis  [3]=parseS();
     UARTindex=4;
    break;
    case  'e':
    UARTaxis  [4]=parseS();
     UARTindex=5;
    break;
    case  'f':
    UARTaxis  [5]=parseS();
     UARTindex=6;
    break;
    case  'g':
    UARTaxis  [6]=parseS();
     UARTindex=7;
    break;     
    case  'h':
    UARTaxis  [7]=parseS();
     UARTindex=8;
    break;     
    default:
    UARTindex=0;
    break;
    }
  }
  if(incomingByte =='S')
  {
incomingByte = Serial.read();
  switch (incomingByte)
  {
    case  'a':  
    UARTaxiss  [0]=parseS();
    break;
    case  'b':
    UARTaxiss  [1]=parseS();
    break;
    case  'c':
    UARTaxiss  [2]=parseS();
    break;
    case  'd':
    UARTaxiss  [3]=parseS();
    break;
    case  'e':
    UARTaxiss  [4]=parseS();
    break;
    case  'f':
    UARTaxiss  [5]=parseS();
    break;
    case  'g':
    UARTaxiss  [6]=parseS();
    break;     
    case  'h':
    UARTaxiss  [7]=parseS();
    break;     
    default:
    break;
    }
  }

  if(incomingByte =='J')
  {
incomingByte = Serial.read();
  switch (incomingByte)
  {
    case  'd':  
    Joystick.setButton(parseS(),1);
    break;
    case  'u':
    Joystick.setButton(parseS(),0);
    break;
    case  'r':
   	Joystick.releaseButton(parseS());
    break;
    case  'p':
    Joystick.pressButton(parseS());
    break;
    default:
    break;
    }
	//  
   }  
    if(incomingByte =='K')
  {
incomingByte = Serial.read();
  switch (incomingByte)
  {
    case  'p':  
    Keyboard.press(Serial.read());
    break;
    case  'r':
    Keyboard.release(Serial.read());
    break;
    case  'a':
    Keyboard.releaseAll();
    break;
    case  'w':
    Keyboard.write(Serial.read());
    break;
    default:
    break;
    }  
   }
// test command  
// P -output to terminal array of rawAxes, 
//  array of UART axes values,
//  array of UART setup range
    if(incomingByte =='p')
  {
    Serial.println("----------------------------------------"); 
    Serial.println("analog axes:[");
    for (int i=0;i<8;i++){Serial.println (axisState[i]);};
    Serial.println("]:end analog");
    Serial.println(); 
    Serial.println("UARTaxis axis:[");
    for (int i=0;i<8;i++){Serial.println (UARTaxis[i]);};
    Serial.println("]:end uart axes");
    Serial.println();     
    Serial.println("UARTaxiss setup:[");
    for (int i=0;i<8;i++){Serial.println (UARTaxiss[i]);};
    Serial.println("]:end");
    Serial.println( temp );
   }
    
}else {delayMicroseconds(200);}; 

/* 
time = micros()-startime; 
Serial.print( "time est :"); 
Serial.print(time);
Serial.println( " mks");
*/
//end UART


//not needed now
/*
 axisState[0]=map( axAxis   ,0, UARTaxiss  [0],-bit12,bit12);
 axisState[1]=map( ayAxis   ,0, UARTaxiss  [1],-bit12,bit12);
 axisState[2]=map( azAxis   ,0, UARTaxiss  [2],-bit9,bit9); 
 axisState[3]=map( arxAxis  ,0, UARTaxiss  [3],-bit9,bit9);
 axisState[4]=map( aryAxis  ,0, UARTaxiss  [4],-bit9,bit9);
 axisState[5]=map( arzAxis  ,0, UARTaxiss  [5],-bit9,bit9);
 axisState[6]=map( aslider1 ,0, UARTaxiss  [6],-bit9,bit9);
 axisState[7]=map( aslider2 ,0, UARTaxiss  [7],-bit9,bit9);
*/
 
if (UARTindex>0){
 // temp=
  axisState[UARTindex-1]=map(  UARTaxis  [UARTindex-1]   ,-UARTaxiss  [UARTindex-1], UARTaxiss  [UARTindex-1],-bit9,bit9); 
  UARTindex=0;
  };

/*
while (Serial.available()>0){ 
 incomingByte = Serial.read();
Serial.write(incomingByte);};
*/
test++;
test++;
if (test>bit9){test=-bit9;};
axisState[7]=bit9*(sin (0.0174*millis()/3)/2+ cos (0.0174*millis()/8)/2);
axisState[5]=bit9*(sin (0.0174*millis()/4));
axisState[6]=test;

axisState[0]=bit15*(sin (0.0174*millis()/3));
axisState[1]=bit15*(cos (0.0174*millis()/3));

     Joystick.setXAxis  (axisState[0]);
     Joystick.setYAxis  (axisState[1]);
     Joystick.setZAxis  (axisState[2]);
     Joystick.setRxAxis (axisState[3]);
     Joystick.setRyAxis (axisState[4]);
     Joystick.setRzAxis (axisState[5]);  
     Joystick.setSlider1(axisState[6]);
     Joystick.setSlider2(axisState[7]);
     
  if (testAutoSendMode == false)  {Joystick.sendState();}
  delay(2); 

 }


 
 int parseS()
{
  bool isNegative = false;
  int value = 0;
  int c;
  c = Serial.read();
  if(c < 0)
    return 0; // zero returned if timeout
  if(c == '-')
      {isNegative = true;}
  do{
 if(c >= '0' && c <= '9')        // is c a digit?
     { value = value * 10 + c - '0';}
      c= Serial.read();  // consume the character we got with peek      
  }
  while( (c >= '0' && c <= '9'));
 if(isNegative){return -value;}else {return value;};
}
 
 
