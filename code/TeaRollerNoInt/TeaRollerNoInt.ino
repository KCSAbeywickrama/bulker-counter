#include "SevSeg.h"
SevSeg seg;

const byte sigPin = 2;
volatile unsigned long count = 0;
unsigned long lastMillis = 0, DEBOUNCE = 800;
bool state, lastState, trigState;

void setup() { 
  pinMode(sigPin, INPUT_PULLUP);
  
  initSeg();
  seg.setNumber(0, 1);
  
  state = digitalRead(sigPin);
  lastState = state;
  trigState = state;
}

void loop() {

  state = digitalRead(sigPin);

  if (state != lastState)
    lastMillis = millis();

  if ((millis() - lastMillis) > DEBOUNCE) {

    if (state != trigState) {
      count++;
      setSeg(count * 5);
      trigState=state;
    }
    
  }
  
  lastState = state;
  
  seg.refreshDisplay();
}


void setSeg(unsigned long num) {
  Serial.println(num);
  if (num < 10000)
    seg.setNumber(num, 1);
  else if (num < 100000)
    seg.setNumber(num / 10);
  else {
    char msg[] = "FULL";
    seg.setChars(msg);
  }
}

void initSeg() {
  byte numDigits = 4;
  byte digitPins[] = {5, 6, 7, 8}; //Digits: 1,2,3,4 <--put one resistor (ex: 220 Ohms, or 330 Ohms, etc, on each digit pin)
  byte segmentPins[] = {3, 9, A2, A4, A5, 4, 10, A3}; //A,B, C, D, E,F, G,DOT -> 7,9,11,12,14,8,10,13
  bool resistorsOnSegments = false; // 'false' means resistors are on digit pins
  byte hardwareConfig = COMMON_CATHODE;// See README.md for options
  bool updateWithDelays = false; // Default 'false' is Recommended
  bool leadingZeros = false; // Use 'true' if you'd like to keep the leading zeros
  bool disableDecPoint = false; // Use 'true' if your decimal point doesn't exist or isn't connected

  seg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments, updateWithDelays, leadingZeros, disableDecPoint);
  seg.setBrightness(90);
}
