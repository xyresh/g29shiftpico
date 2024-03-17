/*
 * Logitech shifter usb mod, using pi pico rp2040
 * 
 * Author Mrayo
 * 
 * this code along with any binaries come as is ,and i am not to be held liable for any malfunctions of your hardware,software etc.
 * this code can be used for any purpose and can be freely modified, redistributed under any license.
 */

#include <Joystick.h>

// Create the Joystick
Joystick_ Joystick1;

// H-shifter mode analog axis thresholds
#define HS_XAXIS_12        400
#define HS_XAXIS_56        500
#define HS_YAXIS_135       800
#define HS_YAXIS_246       300




// Digital inputs definitions
#define DI_REVERSE         1
#define DI_MODE            3


// Shifter state
#define DOWN_SHIFT         -1
#define NO_SHIFT           0
#define UP_SHIFT           1



// LED blink counter
int led=0;

// Shifter state
int shift=NO_SHIFT;

int mode=0;

int b[16];

int gear=0;                          // Default value is neutral

// Constant that maps the phyical pin to the joystick button.
//const int pinToButtonMap = 9;

void setup() {
   // G29 shifter analog inputs configuration 
  pinMode(A0, INPUT_PULLDOWN);   // X axis
  pinMode(A2, INPUT_PULLDOWN);   // Y axis

  pinMode(2, INPUT); 


  for(int i=0; i<16; i++) b[i] = 0;
  b[DI_MODE] =0;
  // Initialize Joystick Library
  Joystick1.begin();

  Serial.begin(115200);
  
}

// Last state of the button
int lastButtonState = 0;

void loop() {

  int x=analogRead(A0);                 // X axis
  int y=analogRead(A2);                 // Y axis

  int _isreverse = digitalRead(2);
  int gir = 0;
  int _gear_ = 0;

if( _isreverse == 1 && gir==6){

      _gear_ = 8;
      b[DI_REVERSE]= 1;

}else{ 

//please calibrate with your own values by using "xyvals()"
//uncomment bellow, check the x and y outputs for each gear position, and assign the correct values that work for you.
//this may need some trial and error, however it will work (i pinky promise ;D)
//xyvals(x,y);

//x == 800 middle
//x < 800 left
//x > 980

//y < 500, down
//y > 850

  {
    if(x<600)                  // Shifter on the left?
    {
      if(y>900) gir=1;       // 1st gear
      if(y<350) gir=2;       // 2nd gear
    }
    else if(x>900)             // Shifter on the right?
    {
      if(y>900&&x>920) gir=5;       // 5th gear
      if(y<350) gir=6;       // 6th gear
     
    }
    else                               // Shifter is in the middle
    {
      if(y>900) gir=3;       // 3rd gear
      if(y<350&&x>600) gir=4;       // 4th gear
    }
   
  }

}


  //reverse button acts as different "joystick button" when not in 6th/reverse position, 
  //can be usefull for truck sims acting as a "split" or "range button"

  if(_isreverse == 1 && x<900){
    Joystick1.setButton(6, HIGH);
    _gear_=gir;

  }else if(_isreverse == 1 && gir==6)
  {
    _gear_=0;
    Joystick1.setButton(7, HIGH);
    Joystick1.setButton(6, LOW);
    Joystick1.setButton(5, LOW);


  }
  else
  {
    Joystick1.setButton(7, LOW);
    Joystick1.setButton(6, LOW);
    _gear_=gir;
  }
  
  
  if(gear!=6) b[DI_REVERSE]=0;         // Reverse gear is allowed only on 6th gear position
  
   if (_gear_ != gear ){
      gear = _gear_;
      desactivar();
      Joystick1.setButton(gear-1, HIGH);
   }
   delay(50);

   
}

void desactivar(){
  // Depress virtual button for current gear
  for(int i = 0; i <= 10 ; i++ )  Joystick1.setButton(i, LOW);
}

void xyvals(int x, int y){
  Serial.print(x);
  Serial.print("\n\n");
  Serial.print(y);
  Serial.print("\n\n");
}
