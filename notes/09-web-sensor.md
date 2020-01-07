# Доступ к датчикам через Web

## Необходимые элементы

* Arduino UNO [Ethernet shield](https://aliexpress.ru/item/32895516422.html)
* Arduino Nano [Ethernet shield](https://aliexpress.ru/item/32294048128.html)
* Универсальный [Ethernet модуль](https://aliexpress.ru/item/32804939507.html)

Не вижу смысла заморачиваться с отдельным модулем для Wi-Fi, так как из реально не так много и взять уже готовую плату с Wi-Fi на борту

* [ESP8266](https://aliexpress.ru/item/32465574655.html) в корпусе Arduino UNO
* [ESP8266](https://aliexpress.ru/item/32647690484.html) плата для разработки
* [ESP32](https://aliexpress.ru/item/4000103411061.html)
* Не будем забывать про [Arduino UNO Wi-Fi](https://store.arduino.cc/usa/arduino-uno-wifi-rev2)
* [Arduino MKR Wi-Fi 1010](https://store.arduino.cc/usa/mkr-wifi-1010)
* [Argon](https://store.particle.io/products/argon)
* [Photon](https://store.particle.io/collections/wifi/products/photon)

## Ethernet

Рисовать схему я не буду, так как соединить две платы сможет каждый. Шилды которые представлены выше работают по шине SPI и соответственно занимают пины 11, 12, 13 для Arduino UNO и Nano и 10 пин используется для Slave Select. Более детально работа SPI рассказывалась в заметки про работу с [SD картой](06-sd-card.md). На шилдах так же имеется SD адаптер.

### Создание web сервера

Я использую плату [Arduino Nano 33 BLE Sense](https://store.arduino.cc/usa/nano-33-ble-sense-with-headers), на ней уже имеется набор сенсоров поэтому я буду использовать их.

```cpp
#include <SPI.h>
#include "Ethernet.h"
#include "Arduino_HTS221.h"
#include "Arduino_LPS22HB.h"

// MAC-адрес, можем указать любой
byte mac[] = {0x12, 0x34, 0x56, 0x78, 0x90, 0xAB };

// IP-адрес будет зависеть от вашей локальной сети
IPAddress ip(10,0,1,20);

// По умолчанию порт для HTTP – это «80»
EthernetServer server(80);

void setup() {
  Serial.begin(9600);

  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);
  pinMode(LEDB, OUTPUT);

  digitalWrite(LEDR, HIGH);
  digitalWrite(LEDG, HIGH);
  digitalWrite(LEDB, HIGH);

  if (!HTS.begin()) {
    Serial.println("Failed to initialize humidity temperature sensor!");

    while (1){
      digitalWrite(LEDR, HIGH);
      delay(300);
      digitalWrite(LEDR, LOW);
      delay(300);
    }
  }

  if (!BARO.begin()) {
    Serial.println("Failed to initialize pressure sensor!");

    while (1){
      digitalWrite(LEDR, HIGH);
      digitalWrite(LEDB, HIGH);
      delay(3000);
      digitalWrite(LEDR, LOW);
      digitalWrite(LEDB, LOW);
      delay(300);
    }
  }

  Ethernet.begin(mac, ip);

  server.begin();

  digitalWrite(LEDG, LOW);
  Serial.println("Server started");
}

void loop(){
  EthernetClient client = server.available();
  if (client) {
    boolean currentLineIsBlank = true;

    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        if (c == '\n' && currentLineIsBlank) {
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          client.println("<meta http-equiv=\"refresh\" content=\"10\">");
          client.println("<body style=\"font-size: 16px;font-family: monospace;\">");

          float temperature = HTS.readTemperature();
          float humidity = HTS.readHumidity();
          float pressure = BARO.readPressure();

          client.println("<div style=\"margin:0 0 10px 0\"><strong>Temperature</strong> = " + String(temperature) + " C</div>");
          client.println("<div style=\"margin:0 0 10px 0\"><strong>Humidity</strong> = " + String(humidity) + " %</div>");
          client.println("<div style=\"margin:0 0 10px 0\"><strong>Pressure</strong> = " + String(pressure) + " kPa</div>");

          client.println("</body>");
          client.println("</html>");
          break;
        }
        if (c == '\n') {
          currentLineIsBlank = true;
        } else if (c != '\r') {
          currentLineIsBlank = false;
        }
      }
    }

    delay(1000);

    client.stop();
    Serial.println("client disonnected");
  }
}
```

Код расположен в директории ```notes/src/09-web-sensor.md```

### Получение адреса от DHCP сервера

Для получения IP адреса следует дополнить блок выше следующий куском кода.

```cpp
Serial.println("Initialize Ethernet with DHCP:");
if (Ethernet.begin(mac) == 0) {
  Serial.println("Failed to configure Ethernet using DHCP");
  if (Ethernet.hardwareStatus() == EthernetNoHardware) {
    Serial.println("Ethernet shield was not found. Sorry, can't run without hardware. :(");
  } else if (Ethernet.linkStatus() == LinkOFF) {
    Serial.println("Ethernet cable is not connected.");
  }

  while (true) {
    delay(1);
  }
}

Serial.print("IP address: ");
Serial.println(Ethernet.localIP());
```

### Передача данных на сервер

Для отправки данных на сервер нужно внести некоторые доработки.

```cpp
EthernetClient client;

void sendData(){
  float temperature = HTS.readTemperature();
  float humidity = HTS.readHumidity();
  float pressure = BARO.readPressure();

  String data = "temperature=" + String(temperature) + "&humidity=" + String(humidity) + "&pressure=" + String(pressure);

  if (client.connect("meteo-station.org",80)) {
    client.println("POST /loadParams HTTP/1.1");
    client.println("Host: meteo-station.org");
    client.println("Content-Type: application/x-www-form-urlencoded");
    client.print("Content-Length: ");
    client.println(data.length());
    client.println();
    client.print(data);
  }

  if (client.connected()) {
    client.stop();
  }

  delay(1000);
}
```

## Wi-Fi

Для работы с Wi-Fi я буду использовать плату ESP-12E (ESP8266), на которой уже имеется модуль.

Код расположен в директории ```notes/src/09-wifi-sensor.md```

### Создание web сервера на WiFi

Я решил не прописывать IP адрес, а получить его автоматически. В коде имеются комментарии для получения статического IP адреса.

```cpp
#include <ESP8266WiFi.h>
#include "OneWire.h"

// Библиотека содержит логин и пароль к точки доступа, содержимое файла можно посмотреть в WifiPass.h.orig
#include "WifiPass.h"

// MAC адрес
uint8_t mac[6] {0x12, 0x34, 0x56, 0x78, 0x90, 0xAC};

OneWire ds(D3);
WiFiServer server(80);

float readTemperature();

void setup(){
  Serial.begin(9600);

  pinMode(LED_BUILTIN, OUTPUT);

  // MAC адрес можно не указывать и будет браться MAC адрес устройства.
  // Если требуется исправить, то следует раскомментировать строку ниже
  //
  // wifi_set_macaddr(0, mac);

  // При подключении к Wi-Fi устройство автоматически получит все настройки сети, при наличии в ней DHCP сервера 
  // Для получения статического IP нужны строки ниже
  //
  // IPAddress ip(10, 0, 1, 25);
  // IPAddress gateway(10, 0, 1, 1);
  // IPAddress subnet(255, 255, 255, 0);
  // WiFi.config(ip, gateway, subnet);

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWD);

  while(WiFi.status() != WL_CONNECTED){
    digitalWrite(LED_BUILTIN, LOW);
    delay(100);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(400);
    Serial.print(".");
  }

  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  server.begin();

  digitalWrite(LED_BUILTIN, LOW);
}

void loop(){
  WiFiClient client = server.available();

  if (client){
    boolean currentLineIsBlank = true;

    while (client.connected()){
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        if (c == '\n' && currentLineIsBlank) {
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          client.println("<meta http-equiv=\"refresh\" content=\"10\">");
          client.println("<body style=\"font-size: 16px;font-family: monospace;\">");

          float temperature = readTemperature();

          client.println("<div style=\"margin:0 0 10px 0\"><strong>Temperature</strong> = " + String(temperature) + " C</div>");

          client.println("</body>");
          client.println("</html>");
          break;
        }
        if (c == '\n') {
          currentLineIsBlank = true;
        } else if (c != '\r') {
          currentLineIsBlank = false;
        }
      }
    }

    delay(1);

    client.stop();
    Serial.println("client disonnected");
  }

}

float readTemperature(){
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

  float temperature = ((data[1] << 8) | data[0]) * 0.0625;

  return temperature;
}
```

Если сравнить с работой через Ethernet, то можно заменить, что верь код схож.
