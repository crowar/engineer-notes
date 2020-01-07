#include <Arduino.h>
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

    float temperature =  ((data[1] << 8) | data[0]) * 0.0625;

    return temperature;
}