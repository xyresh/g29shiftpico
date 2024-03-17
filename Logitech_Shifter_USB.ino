
//Logitech Driving Force Shifter USB Adapter 
//By Armandoiglesias 2018
//Based on Jason Duncan functionreturnfunction Project
//Video tutorial https://www.youtube.com/watch?v=dLpWEu8kCec
//Use Arduino Leonardo
//Install Joystick Library 
//Attribution-NonCommercial-NoDerivatives 4.0 International


#include <Joystick.h>

// Create the Joystick
Joystick_ Joystick1;

// H-shifter mode analog axis thresholds
#define HS_XAXIS_12        400
#define HS_XAXIS_56        500
#define HS_YAXIS_135       800
#define HS_YAXIS_246       300

// Sequential shifter mode analog axis thresholds
#define SS_UPSHIFT_BEGIN   670
#define SS_UPSHIFT_END     600
#define SS_DOWNSHIFT_BEGIN 430
#define SS_DOWNSHIFT_END   500

// Handbrake mode analog axis limits
#define HB_MAXIMUM         530
#define HB_MINIMUM         400
#define HB_RANGE           (HB_MAXIMUM-HB_MINIMUM)

// Digital inputs definitions
#define DI_REVERSE         1
#define DI_MODE            3
#define DI_RED_CENTERRIGHT 4
#define DI_RED_CENTERLEFT  5
#define DI_RED_RIGHT       6
#define DI_RED_LEFT        7
#define DI_BLACK_TOP       8
#define DI_BLACK_RIGHT     9
#define DI_BLACK_LEFT      10
#define DI_BLACK_BOTTOM    11
#define DI_DPAD_RIGHT      12
#define DI_DPAD_LEFT       13
#define DI_DPAD_BOTTOM     14
#define DI_DPAD_TOP        15

// Shifter state
#define DOWN_SHIFT         -1
#define NO_SHIFT           0
#define UP_SHIFT           1

// Shifter mode
#define SHIFTER_MODE       0
#define HANDBRAKE_MODE     1

// LED blink counter
int led=0;

// Shifter state
int shift=NO_SHIFT;

// Handbrake mode
int mode=SHIFTER_MODE;

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
  Serial.print(x);
  Serial.print("\n\n");
  Serial.print(y);
  Serial.print("\n\n");


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

