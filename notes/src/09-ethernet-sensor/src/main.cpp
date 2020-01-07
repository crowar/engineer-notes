#include <Arduino.h>
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
        } 
        else if (c != '\r') {
          currentLineIsBlank = false;
        }
      }
    }

    delay(1000);

    client.stop();
    Serial.println("client disonnected");
  }
}