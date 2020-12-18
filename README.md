# Arduino_Joystick_Keyboard_UARTengine
![win10usbgamecontrols](https://github.com/batbsv/Arduino_Joystick_Keyboard_UARTengine/blob/main/images/win10usbgamecontrols.png)
support Arduino Leonardo, ProMicro boards, based on atmega 32u4 chip.
 conversion https://github.com/MHeironimus/ArduinoJoystickLibrary  for windows 10 pro.
remove all simulation from original and add two Axes slider to Axes HID descriptor.
new init and command below.

Собирательный проект джойстика на Arduino 32u4, 8 осей ,128 кнопок, 
с возможностью подключения к джойстику по UART (через блютуз модуль с телефона или другого устройства)  
базируется на https://github.com/MHeironimus/ArduinoJoystickLibrary , 
но удалены все оси симуляций и добавлены две оси ползунков.
Новое определение джойстка и новые команды выглядят так :

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,

JOYSTICK_TYPE_JOYSTICK, 128, 2,

true, //X

true, //Y

true, //Z

true,//rX

true,//rY

true,//rZ

true, // Slider 1

true // Slider 2

);

Joystick.setSlider1Range(int16_t minimum, int16_t maximum);

Joystick.setSlider2Range(int16_t minimum, int16_t maximum);

Joystick.setSlider1(int16_t value);

Joystick.setSlider2(int16_t value);


-----------------------------------------------------------------------
all commands below fully removed from original libraty

Joystick.setRudderRange(int16_t minimum, int16_t maximum)

Joystick.setRudder(int16_t value)

Joystick.setThrottleRange(int16_t minimum, int16_t maximum)

Joystick.setThrottle(int16_t value)

Joystick.setAcceleratorRange(int16_t minimum, int16_t maximum)

Joystick.setAccelerator(int16_t value)

Joystick.setBrakeRange(int16_t minimum, int16_t maximum)

Joystick.setBrake(int16_t value)

Sets the Brake value. See setBrakeRange for the range.

Joystick.setSteeringRange(int16_t minimum, int16_t maximum)

Joystick.setSteering(int16_t value)

