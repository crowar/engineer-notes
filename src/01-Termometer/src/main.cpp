#include <Arduino.h>

// Подключение библиотеки для работы с датчиком
#include <DHT.h>

// Номер пина к которому подсоединен датчик
#define DHTPIN 2

// Создание объекта DHT
DHT dht(DHTPIN, DHT11);

void setup() {
    Serial.begin(9600);
    dht.begin();
}

void loop() {

    // Так как датчик DHT-11 можно опрашивать не чаще одного раза в секунду то выставляем задержку в одну секунды. Для датчика DHT-22 требуется задержка в 2 секунды
    delay(1000);

    // Считываем влажность
    float h = dht.readHumidity();

    // Считываем температуру
    float t = dht.readTemperature();

    // Проверяем успешность считывания данных
    if (isnan(h) || isnan(t)) {
        Serial.println("Не удается считать показания");
        return;
    }

    // Выводим показания в Serial Monitor
    Serial.print("Влажность: ");
    Serial.print(h);
    Serial.print("%\tТемпература: ");
    Serial.print(t);
    Serial.println(" °C");
}