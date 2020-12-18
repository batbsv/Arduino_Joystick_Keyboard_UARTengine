
#include <Keyboard.h>
#include <Joystick.h>

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

int incomingByte = 0;

void setup() {
  Serial.begin (115200); 
  Serial1.begin(115200);
  Keyboard.begin(); 

  
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

     Joystick.setXAxis( random());
     Joystick.setYAxis( random());
     Joystick.setZAxis( random());
     Joystick.setRxAxis(random());
     Joystick.setRyAxis(random());
     Joystick.setRzAxis(random());  
     Joystick.setSlider1(random());
     Joystick.setSlider2(random());
     Joystick.pressButton (random (127));
     Joystick.releaseButton(random (127));
  
while (Serial.available()>0){ 
 incomingByte = Serial.read();
Serial.write(incomingByte);};
  if (testAutoSendMode == false)  {Joystick.sendState();}
  delay(5); 

 }
 
