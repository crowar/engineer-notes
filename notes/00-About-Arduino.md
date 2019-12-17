# Вступление

Долго думал с чего начать, решил начать с небольших проектов на Arduino.

Arduino - это открытая аппаратно-программный платформа, нацелена на неопытных пользователей, для старта изучения основ программирования и/или робототехники. В основе платы стоит контроллер Atmega в зависимости от плат модификация контроллера может отличаться. Более подробно можно почитать на [сайте](https://www.arduino.cc/en/Guide/Introduction).

## Платы и различные полезные предметы

### Семейство Arduino

На старте нам понадобится плата Arduino, купить можно на аликеке:

* [Arduino Uno](https://ru.aliexpress.com/item/33009726379.html?spm=a2g0o.productlist.0.0.25974fd9fmR77m&algo_pvid=a4c2fe94-1d21-4bea-8870-45489f920ec2&algo_expid=a4c2fe94-1d21-4bea-8870-45489f920ec2-4&btsid=262d814f-3b3d-4b60-88ac-79f9d32b5016&ws_ab_test=searchweb0_0,searchweb201602_2,searchweb201603_52) одна из популярных плат, имеет много дополнительных плат расширений.
* [Arduino Nano](https://ru.aliexpress.com/item/32242048437.html?spm=a2g0o.productlist.0.0.2cef6623Li5MTg&algo_pvid=c2880935-daa7-4505-8ef1-c55f42b446ff&algo_expid=c2880935-daa7-4505-8ef1-c55f42b446ff-8&btsid=aabb2643-2cef-4d2f-a6ba-15aff2c1031d&ws_ab_test=searchweb0_0,searchweb201602_2,searchweb201603_52), достаточно помпактная плата, может поместиться с спичечный коробок.
* [Arduino Mega](https://www.aliexpress.com/item/4000235952850.html?spm=a2g0o.productlist.0.0.38083368Q1yl7N&algo_pvid=26211d0d-e210-431f-8799-ccdfd9d326c1&algo_expid=26211d0d-e210-431f-8799-ccdfd9d326c1-0&btsid=3599d33c-0813-4d68-963f-72a0b314fcf0&ws_ab_test=searchweb0_0,searchweb201602_2,searchweb201603_53), одна из самых больших плат из семейства ардуино. Имеет большое количестно пинов, подключить можно практически все, что душе угодно.
* [Arduino Leonardo](https://www.aliexpress.com/item/32923016834.html?spm=a2g0o.productlist.0.0.270416ffxQOuIs&algo_pvid=219113a5-91de-4920-90aa-df4a61b02d9f&algo_expid=219113a5-91de-4920-90aa-df4a61b02d9f-2&btsid=58ab28fb-ee6e-48b6-b5bc-07a52f0ac308&ws_ab_test=searchweb0_0,searchweb201602_2,searchweb201603_53) может быть в класическом форм факторе или же своей [уменьшенной версии](https://www.aliexpress.com/item/32768308647.html?spm=a2g0o.productlist.0.0.270416ffxQOuIs&algo_pvid=219113a5-91de-4920-90aa-df4a61b02d9f&algo_expid=219113a5-91de-4920-90aa-df4a61b02d9f-0&btsid=58ab28fb-ee6e-48b6-b5bc-07a52f0ac308&ws_ab_test=searchweb0_0,searchweb201602_2,searchweb201603_53). Преимещество контроллера установленного на этой плате в том, что он имеет встроенную поддержку USB устройства и может эмулировать: мышку, клавиатуру или что то другое.

Так же для фанатов всего настоящего, а не подделок с поднебесной, можно ознакомиться с продукцией на [официальном сайте](https://store.arduino.cc/usa/arduino/boards-modules). Я бы рекомендовал преобрести плату [Arduino Nano 33 BLE Sense](https://store.arduino.cc/usa/nano-33-ble-sense-with-headers), на ней уже имеется большое количество часто используемых датчиков и купив только её можно много чего сделать.

### Платы на контроллере ESP

* [ESP8266](https://www.aliexpress.com/item/32647690484.html?spm=a2g0o.productlist.0.0.1a341549V9pxHT&algo_pvid=b5c723ce-b6ad-4f68-b77b-2fb8dfbfbc1e&algo_expid=b5c723ce-b6ad-4f68-b77b-2fb8dfbfbc1e-0&btsid=4e479a99-f776-47c9-8176-5258ee68b3ab&ws_ab_test=searchweb0_0,searchweb201602_2,searchweb201603_53) в виде платы для разработки или в виде [модуля для пайки](https://www.aliexpress.com/item/32633529267.html?spm=a2g0o.productlist.0.0.1a341549V9pxHT&algo_pvid=b5c723ce-b6ad-4f68-b77b-2fb8dfbfbc1e&algo_expid=b5c723ce-b6ad-4f68-b77b-2fb8dfbfbc1e-7&btsid=4e479a99-f776-47c9-8176-5258ee68b3ab&ws_ab_test=searchweb0_0,searchweb201602_2,searchweb201603_53) на готовую плат. Особенность платы в том, что она уже имеет на своем борту WiFi модуль
* [ESP32](https://www.aliexpress.com/item/32990513451.html?spm=a2g0o.productlist.0.0.65af77b2Xls4ts&s=p&algo_pvid=fa7341b5-5724-4723-be10-50aacf2051c6&algo_expid=fa7341b5-5724-4723-be10-50aacf2051c6-17&btsid=124954a2-2abf-49cb-aa01-98c5c37043ae&ws_ab_test=searchweb0_0,searchweb201602_2,searchweb201603_53) в виде платы для [разработчика](https://www.aliexpress.com/item/32967151948.html?spm=a2g0o.productlist.0.0.6ffe48felGy1qa&algo_pvid=a6e71bd5-b2ef-4b6c-b890-e7e2abd6c566&algo_expid=a6e71bd5-b2ef-4b6c-b890-e7e2abd6c566-21&btsid=10f6bdb6-ce97-4a8b-8bdf-bbc3aa28613e&ws_ab_test=searchweb0_0,searchweb201602_2,searchweb201603_53), с [дисплеем](https://www.aliexpress.com/item/4000061163947.html?spm=a2g0o.productlist.0.0.65af77b2Xls4ts&algo_pvid=fa7341b5-5724-4723-be10-50aacf2051c6&algo_expid=fa7341b5-5724-4723-be10-50aacf2051c6-4&btsid=124954a2-2abf-49cb-aa01-98c5c37043ae&ws_ab_test=searchweb0_0,searchweb201602_2,searchweb201603_53), с [GSM модулем](https://www.aliexpress.com/item/4000311529070.html?spm=a2g0o.productlist.0.0.6ffe48felGy1qa&algo_pvid=a6e71bd5-b2ef-4b6c-b890-e7e2abd6c566&algo_expid=a6e71bd5-b2ef-4b6c-b890-e7e2abd6c566-32&btsid=10f6bdb6-ce97-4a8b-8bdf-bbc3aa28613e&ws_ab_test=searchweb0_0,searchweb201602_2,searchweb201603_53) на борту

### Другие полезности

Можно заказать ещё пару вещей:

* [Макетка](https://ru.aliexpress.com/item/32432740751.html?spm=a2g0o.productlist.0.0.d7b03000rVbFVh&algo_pvid=57930d87-1770-4d50-b1e0-da343cefe770&algo_expid=57930d87-1770-4d50-b1e0-da343cefe770-5&btsid=af2fac3e-e736-42c9-8435-5fbc0623bc91&ws_ab_test=searchweb0_0,searchweb201602_2,searchweb201603_52)
* [Проводки разного вида](https://ru.aliexpress.com/item/32662824675.html?spm=a2g0o.productlist.0.0.d7b03000rVbFVh&algo_pvid=57930d87-1770-4d50-b1e0-da343cefe770&algo_expid=57930d87-1770-4d50-b1e0-da343cefe770-2&btsid=af2fac3e-e736-42c9-8435-5fbc0623bc91&ws_ab_test=searchweb0_0,searchweb201602_2,searchweb201603_52)

## Среды разработки

### PlatformIO

По работе со средой platformio есть отличная документация на [официальном сайте](https://platformio.org/install/ide?install=vscode). Более удобное средство нежеди классика. Имеется интеграции со средами Visual Studio и Jetbrains CLion

### Arduino IDE

Класическая среда разработки, хорошо описанна и без намека на нормальную разработку. Arduino IDE можно [скачать](https://www.arduino.cc/en/Main/Software) с официального сайта.

![Arduino IDE](../img/00/arduino-ide.png)

Для понимания базовой работы с платой, можно открыть пример ```File -> Examples -> 01. Basics -> Blink```. Детальное описание этого примера описано на [официальном сайте](https://www.arduino.cc/en/Tutorial/Blink)

Для загрузки скетча на плату, требуется указать тип платы ```Tools -> Board -> Arduino UNO``` (либо другая в зависимости от платы которая есть у вас), далее требуется указать на каком порту подключена плата это можно сделать ```Tools -> Port -> COM_N```. После загрузки данного скетча на плату (```Sketch -> Upload```) на плате начнет мигать светодиод с промежутком в одну секунду.

## Заметки

Купить все о чем я буду писать можно и в месных магазинах. Вот некоторые из них:

* [Delta chip](https://go.2gis.com/qny6b)
* Так же есть в [тастоке](https://go.2gis.com/2oxdd) у них есть сайт на котором можно поискать интересные модули [ba3ar.kz](http://ba3ar.kz/)

Так же есть и оригинальные магазины различной электронники:

* [adafruit](https://www.adafruit.com/) на сайте есть блог в котором часто собирают и рассказывают про интересные приборы, платы, поделки и т.д. Так же на сайте есть интернет магазин, в котором продоют много оригинальных товаром.
* [sparkfun](https://www.sparkfun.com/) сайт интересен своими собственными разработками. У них часто появляются платы которые как раз подходят под мой проект, по размерам, по мощности и другим параметрам.
* [makeblock](https://www.makeblock.com/) данная компания производит уже готовые устройства, есть на что посмотреть и чем вдохновиться
