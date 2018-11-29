
#include "FastLED.h"

#define NUM_LEDS 10
#define DATA_PIN 4

const int buttonL = 0;
const int button = 1;
const int buttonR = 2;

int var=0;
int maxx=7;
int hue0 = 0, hue1 = 0;

bool toggle = false;
bool once = false;
bool on = false;

boolean btnState, btn_flag, hold_flag, btnStateL, btn_flagL, hold_flagL, btnStateR, btn_flagR, hold_flagR;
unsigned long btn_timer, btn_timerL, btn_timerR;
byte btn_counter, btn_counterL, btn_counterR;
#define BTN_TIMEOUT 400

bool _ButtonNow = false;
bool _ButtonPress = false;
bool _ButtonHold = false;

bool _ButtonNowL = false;
bool _ButtonPressL = false;
bool _ButtonHoldL = false;

bool _ButtonNowR = false;
bool _ButtonPressR = false;
bool _ButtonHoldR = false;


CRGB leds[NUM_LEDS];

void setup() {
  pinMode(buttonL, INPUT_PULLUP);
  pinMode(button, INPUT_PULLUP);
  pinMode(buttonR, INPUT_PULLUP);
 // pinMode(13, OUTPUT);
  Serial.begin(9600);
  FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);
  
  FastLED.setBrightness(255);
  fill_solid(leds, NUM_LEDS,  CHSV(100, 255, 255) );
  FastLED.show();
  delay(500);
  FastLED.setBrightness(0);
  fill_solid(leds, NUM_LEDS,  CHSV(hue0, 255, 255) );
  FastLED.show();
}

void loop() {
    
GetButtonInput();
GetButtonInputL();
GetButtonInputR();
cycleBoth();
cycleLeft();
cycleRight();
   }



void GetButtonInput(){
  static uint16_t count = 0;
  _ButtonNow = false;
  _ButtonPress = false;
  if (!digitalRead(button)) {
    _ButtonNow = true;
    count++;
    Serial.println(count);
    delay(75);
  } else {
    if (count > 2 && count < 10) {
      _ButtonPress = true;
    //  Serial.println(count);
            on = !on;
       if (on == false) {
          FastLED.setBrightness(0);
          //FastLED.show();
          Serial.println("off");          
        }      
      if (on == true) {
          //fill_solid(leds, NUM_LEDS,  CHSV(100, 255, 255) );
          FastLED.setBrightness(255);
          //FastLED.show();
         Serial.println("on");                
        }
        
    }
    count = 0;
  }
  if (count > 10) {
    _ButtonHold = true;
    Serial.println(count);
  } else {
    _ButtonHold = false;
  }
  FastLED.show(); 
}



void GetButtonInputL(){
  static uint16_t count = 0;
  _ButtonNowL = false;
  _ButtonPressL = false;
  if (!digitalRead(buttonL)) {
    _ButtonNowL = true;
    count++;
    Serial.println(count);
    delay(75);
  } else {
    if (count > 2 && count < 10) {
      _ButtonPressL = true;
    //  Serial.println(count);
    }
    count = 0;
  }
  if (count > 10) {
    _ButtonHoldL = true;
    Serial.println(count);
  } else {
    _ButtonHoldL = false;
  } 
}

void GetButtonInputR(){
  static uint16_t count = 0;
  _ButtonNowR = false;
  _ButtonPressR = false;
  if (!digitalRead(buttonR)) {
    _ButtonNowR = true;
    count++;
    Serial.println(count);
    delay(75);
  } else {
    if (count > 2 && count < 10) {
      _ButtonPressR = true;
    //  Serial.println(count);
    }
    count = 0;
  }
  if (count > 10) {
    _ButtonHoldR = true;
    Serial.println(count);
  } else {
    _ButtonHoldR = false;
  } 
}


void cycleBoth() {
     
  if(_ButtonHold)
  {
    hue0++;
    hue1=hue0;    
    fill_solid(leds, NUM_LEDS, CHSV(hue0, 255, 255));
    FastLED.show();
    delay(30);
  }
}

void cycleLeft() {
  if(_ButtonHoldL)
  {
    hue0++;    
    leds[1]=CHSV(hue0, 255, 255);
    FastLED.show();
    delay(30);
  }
}

void cycleRight() {
 
  if(_ButtonHoldR)
  {
    hue1++;    
    leds[0]=CHSV(hue1, 255, 255);
    FastLED.show();
    delay(30);
  }
}


