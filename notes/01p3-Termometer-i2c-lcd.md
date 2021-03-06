# Градусник с LCD дисплеем

## Нужные элементы

Датчики:

* [DHT-11](https://www.aliexpress.com/item/33005500534.html)
* [DHT-11 в готовом модуле](https://ru.aliexpress.com/item/1059518033.html)
* [DHT-22](https://ru.aliexpress.com/item/33052251953.html)

Дисплей:

* [LCD дисплей 2x16](https://www.aliexpress.com/item/32786773241.html)
* [LCD дисплей 4x20](https://www.aliexpress.com/item/32831845529.html)
* [I2C модуль для дисплея](https://www.aliexpress.com/item/32984942286.html)

Рекомендую сразу брать дисплей с уже припаянным I2C модулей, выйдет дешевле и не надо будет паять

## Схема подключения

Как работать с датчиками DHT-NN разбирались в [статье чуть ранее](01-Thermometer.md).

Для подключения дисплея будем использовать подключение по [I2C](https://en.wikipedia.org/wiki/I%C2%B2C), для тех кому википедии не достаточно, то есть [видео](https://www.youtube.com/watch?v=_4KD29qnhNM)

Для разных плат могут использовать разные порты, для более детальной информации нужно смотреть описание платы. Вот небольшой перечень распространенных плат

|Наименование платы|SDA|SCL|
|---|:-:|:-:|
|Arduino Uno|A4|A5|
|Arduino Nano|A4|A5|
|Arduino Micro|2|3|
|Arduino Mega 2560|20|21|
|Arduino Leonardo|2|3|
|Arduino Due|20|21|
|ESP-12E (8266)|D2|D1|

Схема подключения датчика и дисплея:

![Схема подключения](../img/01/termometer-with-i2c-lcd.png)

## Написание кода

Для работы с LCD дисплеем нам потребуется библиотека [LiquidCrystal_I2C](https://github.com/johnrickman/LiquidCrystal_I2C.git), можно установить аналогичным способом или при использовании PlatformIO можно добавить в файл ```platformio.ini``` зависимость от данной библиотеки и она будет скачена в автоматическом режиме.

```ini
lib_deps =
https://github.com/johnrickman/LiquidCrystal_I2C.git
```

Теперь пришло время доработать наш код и добавить отображение температуры на дисплей

```cpp
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
    lcd.print("Temp: "+ String(t) + " C");
    lcd.setCursor(12, 1);
    lcd.write(0);

    Serial.print("Влажность: ");
    Serial.print(h);
    Serial.print("%\tТемпература: ");
    Serial.print(t);
    Serial.println(" °C");
}
```

Загружаем прошивку на плату и проверяем работу. Примерно вот так это выглядит у меня

![Termometer photo with lcd display](../img/01/termometer-with-i2c-lcd-photo.png)
