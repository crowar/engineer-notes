#include <Arduino.h>
#include <DHT.h>
#include <TM1637Display.h>

#define DHTPIN 2
#define CLKPIN 3
#define DIOPIN 4

#define DELAY   2000

DHT dht(DHTPIN, DHT11);
TM1637Display display(CLKPIN, DIOPIN);

void setSegmentsFormatTemperature(int num);

void setup() {
    Serial.begin(9600);
    dht.begin();
    display.setBrightness(0, true);
}

void loop() {
    delay(DELAY);

    float h = dht.readHumidity();
    float t = dht.readTemperature();

    if (isnan(h) || isnan(t)) {
        Serial.println("Не удается считать показания");
        return;
    }

    setSegmentsFormatTemperature((int) t);

    // Выводим показания в Serial Monitor
    Serial.print("Влажность: ");
    Serial.print(h);
    Serial.print("%\tТемпература: ");
    Serial.print(t);
    Serial.println(" °C");
}

void setSegmentsFormatTemperature(int num) {
    uint8_t data[] = {0x00, 0x00, 0b01100011, 0b00111001};

    for (int i = 1; i >= 0; --i) {
        uint8_t digit = num % 10;

        if (digit == 0 && num == 0)
            data[i] = 0;
        else
            data[i] = display.encodeDigit(digit);

        num /= 10;
    }

    display.setSegments(data);
}