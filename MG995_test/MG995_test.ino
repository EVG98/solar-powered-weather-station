// Firmware test for MG995 Servo Motor
// Connect the MG995 to 5V and GND
// Connect the data pin to D3 on the Arduino

const int SERVO = 3;
unsigned int pulse = 0;
int spin = 1;

void setup() {
  pinMode(SERVO, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if (spin == 1) {
    if (pulse >= 255) {
      spin = -1;
    }
  } else if (spin == -1) {
    if (pulse <= 0) {
      spin = 1;
    }
  }
  
  pulse += spin;
  setPulse();

  delay(100);
}

void setPulse() {
  analogWrite(SERVO, pulse);
}
