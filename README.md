# Arduino_Joystick_Keyboard_UARTengine
собирательный проект джойстика на Arduino 32u4, 8 осей ,128 кнопок, с возможностью подключения к джойстику по UART (через блютуз модуль с телефона или другого устройства)  

базируется на https://github.com/MHeironimus/ArduinoJoystickLibrary , 
но удалены все оси симуляций и добавлены две оси ползунки.
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

Joystick.setSlider1Range(min, max);

Joystick.setSlider2Range(min, max);

Joystick.setSlider1( value );

Joystick.setSlider2( vakue);
