#include <Arduino.h>
#include "OneWire.h"
#include "LiquidCrystal_I2C.h"

OneWire ds(3);
LiquidCrystal_I2C lcd(0x27,16,2);  

byte tempChar[] = {0x07,0x05,0x07,0x00,0x00,0x00,0x00,0x00};

void setup(){
    lcd.init();
    lcd.backlight();
    lcd.createChar(0, tempChar);
}

void loop(){
    byte data[2];

    ds.reset();
    ds.write(0xCC);
    ds.write(0x44);

    delay(1000);

    ds.reset();
    ds.write(0xCC);
    ds.write(0xBE);

    data[0] = ds.read();
    data[1] = ds.read();

    float temperature =  ((data[1] << 8) | data[0]) * 0.0625;
  
    lcd.setCursor(0,0);
    lcd.print("Temp: " + String(temperature) + "  C");
    lcd.setCursor(12, 0);
    lcd.write(0);
}