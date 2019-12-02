#include <Arduino.h>

const int LightSensorPin = A0;

void setup() {
  Serial.begin(9600);
  pinMode(LightSensorPin, INPUT);
}

void loop() {
  int lightCount = analogRead( LightSensorPin );
  Serial.println( lightCount );
  delay(200);
}