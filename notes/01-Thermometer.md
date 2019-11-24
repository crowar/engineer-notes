 # Грудусник

## Нужные элементы

Датчики:
* [DHT-11](https://www.aliexpress.com/item/33005500534.html?spm=a2g0o.productlist.0.0.64f25d39hXA0pY&algo_pvid=d4cc7b7e-71d9-4f4d-be1e-cd2dd71ed522&algo_expid=d4cc7b7e-71d9-4f4d-be1e-cd2dd71ed522-0&btsid=9f479f34-2398-411a-a638-03b82ab7107b&ws_ab_test=searchweb0_0,searchweb201602_2,searchweb201603_52)
* [DHT-11 в готовом модуле](https://ru.aliexpress.com/item/1059518033.html?spm=a2g0o.productlist.0.0.64f25d39hXA0pY&algo_pvid=d4cc7b7e-71d9-4f4d-be1e-cd2dd71ed522&algo_expid=d4cc7b7e-71d9-4f4d-be1e-cd2dd71ed522-2&btsid=9f479f34-2398-411a-a638-03b82ab7107b&ws_ab_test=searchweb0_0,searchweb201602_2,searchweb201603_52)
* [DHT-22](https://ru.aliexpress.com/item/33052251953.html?spm=a2g0o.productlist.0.0.6a7057e9d2r9lk&algo_pvid=b3d264de-1c69-42ec-8367-d6f398f48aa9&algo_expid=b3d264de-1c69-42ec-8367-d6f398f48aa9-1&btsid=0d424122-1704-4e4b-8880-440eae08cafc&ws_ab_test=searchweb0_0,searchweb201602_2,searchweb201603_52)

## Описание датчика
Датчик DHT-NN измеряет температуру и влажность

Датчик DHT-11:
* определение влажности в диапазоне 20-80%
* определение температуры от 0°C до +50°C
* частота опроса 1 раз в секунду

Датчик DHT-22:
* определение влажности в диапазоне 0-100%
* определение температуры от -40°C до +125°C
* частота опроса 1 раз в 2 секунды

У меня имеется датчик DHT-11, но работать с такими датчиками не отличается. Датчики DHT имеют 4 вывода:
* питание.
* вывод данных
* не используется.
* GND (земля).

Между выводами питания и вывода данных нужно разместить резистор номиналом 10 кОм. Датчик DHT часто продается в виде готового модуля. В этом случае он имеет три вывода и подключается без резистора, т.к. резистор уже есть на плате.

Схема подключения датчика с резистором:

![Arduino IDE](../img/01/termometer-breadboard-view.png)

После подключения и соединения всех элементов нужно написать немного кода. 

## Написание кода

Для работы с датчиком DHT имеется библиотека, которую можно установить из самой среды. Требуется зайти ```Scketch -> Include library -> Manage libraries``` и в окне менеджера найти библиотеку ```DHT sensor library```.

Теперь можно перейти к написанию кода

```c
// Подключение библиотеки для работы с датчиком
#include "DHT.h"

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
```

Пришла пора загружать код на плату ```Sketch -> Upload``` и сразу после загрузки переходим в Serial Monitor для проверки работы нашего градусника ```Tools -> Serial Monitor```

![Serial Monitor](../img/01/serial-monitor.png)

Как изменить температуру думаю сообразите самостоятельно.