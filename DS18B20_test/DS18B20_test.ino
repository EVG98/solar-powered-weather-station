// Firmware test for DS18B20 Temperature Sensor
// Connect the DS18B20 to 5V and GND
// Connect the data pin to D2 on the Arduino
// Connect a 4.7k pullup resistor to the data line

#include <OneWire.h>
#include <DallasTemperature.h>
#include "TimerOne.h"

float lastKnownTemperature;

OneWire oneWire(2);
DallasTemperature sensor(&oneWire);

void setup() {
  sensor.begin();
  Serial.begin(9600);

  Timer1.initialize(3000000);
  Timer1.attachInterrupt(readTemperature);
}

void loop() {
  
}

void readTemperature() {
  sensor.requestTemperatures();

  lastKnownTemperature = sensor.getTempCByIndex(0) * 1.8 + 32;

  Serial.print("Temperature: ");
  Serial.print(lastKnownTemperature);
  Serial.println(" Fahrenheit");
}
