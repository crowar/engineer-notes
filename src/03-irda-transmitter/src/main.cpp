#include <Arduino.h>
#include <IRremote.h>

IRsend irsend;

void setup()
{
}

void loop()
{
  irsend.sendLG(0x20DF10EF, 32);
  delay(20000);
}