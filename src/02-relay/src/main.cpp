#include <Arduino.h>

const int RelayPin = 4;

void setup() {
  pinMode(RelayPin, OUTPUT);
  digitalWrite(RelayPin, LOW);
}
void loop() {
  digitalWrite(RelayPin, HIGH);
  delay(3000);

  digitalWrite(RelayPin, LOW);
  delay(3000);
}