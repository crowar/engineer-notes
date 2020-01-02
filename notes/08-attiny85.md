# Работа с сервой

## Необходимые элементы

* [Attiny85](https://aliexpress.ru/item/4000059212852.html?spm=a2g0o.productlist.0.0.7b4c2815UUfJG9&algo_pvid=cb164c26-8d08-48cc-a1c8-dbbc4074c552&algo_expid=cb164c26-8d08-48cc-a1c8-dbbc4074c552-7&btsid=2934d9bb-818a-42c7-8802-72694601d6e0&ws_ab_test=searchweb0_0,searchweb201602_2,searchweb201603_53)

При желании можно использовать Attiny25 или Attiny45.

## Схема подключения

Для прошивки нашего контроллера нужно использовать програматор, но при отсутствии такой штуки, можно взять любую плату Arduino,
у меня для таких целей валяется UNO. Но для того, что бы она начала работать как програматор, требуется загрузить специальную прошивку. Найти код можно в Arduino IDE пройдя ```File > Examples > ArduinoISP > ArduinoISP```. Более подробно можно почитать на [официальном сайте](https://www.arduino.cc/en/tutorial/arduinoISP)

![Arduino as ISP with Attiny85](../img/08/Arduino-Attiny85.png)

Далее на чип можно загрузить нашу прошивку. Я решил использовать пример с [термометром](01p4-Termometer-ds18b20.md) и выводить показания на LCD дисплей как в [примере ранее](01p3-Termometer-i2c-lcd.md)

![Attiny85 termometer](../img/08/Attiny85.png)

## Написание кода

Код ничем не отличается и смело можно переносить проекты на данный чип.

```cpp
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
```

## Выводы

Данный микроконтроллер может использоваться для различных устройств не трубовательных к питанию. Микроконтроллер может работать при токе 1.8V, при этом будет потреблять всего 0.3mA. Соотвественно можно собрать схему с солнечной батареей и аккомулятором Ni-MH, отлично работающей при низких температурах.

Как вариант можно собрать внешний автономный блок для измерения температуры за бортом и передача этой информации на главный контроллер.

Все характеристики можно посмотреть в [описании](https://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-2586-AVR-8-bit-Microcontroller-ATtiny25-ATtiny45-ATtiny85_Datasheet.pdf) к контроллеру.

## Фотофиниш

Градусник на Attiny85

![Attiny85 термометр](../img/08/attiny85-photo-1.jpg)

Повысим немного температуру

![Attiny85 термометр тест работы](../img/08/attiny85-photo-2.jpg)

Все работает как и планировали. При отсутствии дисплея можно значительно было бы понизить напряжение питания. На примере плата работает от 5V.
