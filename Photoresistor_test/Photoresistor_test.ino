// Firmware test for Photoresistors
// Construct two voltage divider networks consisting of
//  510 Ohm resistors in series with photoresistors
// Apply 5V across the networks
// Connect the center point of each network
//  to pins A0 and A1 on the Arduino respectively

#include "TimerOne.h"

const int PHOTO_1 = 0;
const int PHOTO_2 = 1;

int suggestedSpin = 0;
const bool reversed = false;

const int threshold_low = 100;
const int threshold_high = 200;
int threshold;

void setup() {
  pinMode(PHOTO_1, INPUT);
  pinMode(PHOTO_2, INPUT);
  Serial.begin(9600);

  Timer1.initialize(100000);
  Timer1.attachInterrupt(setSuggestedSpin);
}

void loop() {
  
}

void setSuggestedSpin() {
  int p1, p2;
  if (!reversed) {
     p1 = analogRead(PHOTO_1);
     p2 = analogRead(PHOTO_2);
  } else {
     p1 = analogRead(PHOTO_2);
     p2 = analogRead(PHOTO_1);
  }

  if (p1 > p2) {
    if (p1 - p2 > threshold) {
      suggestedSpin = 1;
      threshold = threshold_low;
    } else if (p1 - p2 < threshold) {
      suggestedSpin = 0;
      threshold = threshold_high;
    }
  } else if (p2 > p1) {
    if (p1 - p2 < -threshold) {
      suggestedSpin = -1;
      threshold = threshold_low;
    } else if (p1 - p2 > -threshold) {
      suggestedSpin = 0;
      threshold = threshold_high;
    }
  }
  
  Serial.println(suggestedSpin);
}
