# g29shiftpico
pi pico diy usb adapter for logitech g29 shifter

this depends on the joystick library:
https://github.com/MHeironimus/ArduinoJoystickLibrary

there are many adapters using arduino nano and such, however this is a much cheaper solution.
you can compile this for the pi pico using the arduino IDE or grab an already compiled uf2 firmware and drag and drop on to your pi pico

the pin configuration doesn't matter but in order to make this build as seamless as possible you can use this config:


| pico pin  | DB9 pin | 
| --------- | ------- |
|  31/GP26  | 4       |
|  4/GP2    | 2       |
|  GND      | 6       |
|  VCC/VBUS | 7       |
| 34/GP28   | 8       |

please note that it may not index the gears correctly for your specific shifter, if so calibrate your X,Y values using the serial monitor using the arduino IDE.
