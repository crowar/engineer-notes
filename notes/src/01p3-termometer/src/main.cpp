#include <Arduino.h>

#include <DHT.h>
#include <LiquidCrystal_I2C.h>

DHT dht(2, DHT11);
LiquidCrystal_I2C lcd(0x27,16,2);  

byte tempChar[] = {0x07,0x05,0x07,0x00,0x00,0x00,0x00,0x00};

void setup() {
    Serial.begin(9600);
    dht.begin();

    lcd.init();
    lcd.backlight();
    lcd.createChar(0, tempChar);
}

void loop() {
    delay(1000);

    float h = dht.readHumidity();
    float t = dht.readTemperature();
    if (isnan(h) || isnan(t)) {
        Serial.println("Не удается считать показания");
        return;
    }

    //Выводим показания на дисплей
    lcd.setCursor(0,0);
    lcd.print("Humidity: " + String(h) + "%");
    lcd.setCursor(0,1);
    lcd.print("Temp: "+ String(t) + "  C");
    lcd.setCursor(12, 1);
    lcd.write(0);

    Serial.print("Влажность: ");
    Serial.print(h);
    Serial.print("%\tТемпература: ");
    Serial.print(t);
    Serial.println(" °C");
}