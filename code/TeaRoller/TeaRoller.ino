#include "SevSeg.h"
SevSeg seg;

const byte sigPin = 2;
volatile unsigned long count = 0;
unsigned long num_now = 0;

void setup() {
  pinMode(sigPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(sigPin), isr, CHANGE);
  initSeg();
  seg.setNumber(num_now, 1);
}

void loop() {
  updateSeg(count * 5);
  seg.refreshDisplay();
}

void isr() {
  count++;
}

void updateSeg(unsigned long num) {
  if (num_now != num) {
    num_now = num;
    if (num_now < 10000)
      seg.setNumber(num_now, 1);
    else if (num_now < 100000)
      seg.setNumber(num_now / 10);
    else {
      char msg[] = "FULL";
      seg.setChars(msg);
    }

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
