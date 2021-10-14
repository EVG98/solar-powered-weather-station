#include "TimerOne.h"

const int PHOTO_1 = 0;
const int PHOTO_2 = 1;
const int SERVO = 3;

int suggestedSpin = 0;
unsigned int pulse = 128;
int spin = 1;

const int threshold_low = 100;
const int threshold_high = 200;
int threshold;
const bool reversed = false;

void setup() {
  pinMode(SERVO, OUTPUT);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  Serial.begin(9600);

  Timer1.initialize(100000);
  Timer1.attachInterrupt(handleServo);
}

void loop() {
  
}

void handleServo() {
  setSuggestedSpin();
  setPulse();
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
}

void setPulse() {
  if (suggestedSpin == -1) {
    if (pulse > 0) {
      pulse = pulse + suggestedSpin;
    }
  } else if (suggestedSpin == 1) {
    if (pulse < 255) {
      pulse = pulse + suggestedSpin;
    }
  }
  
  Serial.println(pulse);
  analogWrite(SERVO, pulse);
}
