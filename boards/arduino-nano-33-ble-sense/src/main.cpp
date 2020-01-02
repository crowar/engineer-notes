#include <Arduino.h>
#include <Arduino_LPS22HB.h>
#include <Arduino_HTS221.h>

void setup() {
  // pinMode(LEDR, OUTPUT);
  // pinMode(LEDG, OUTPUT);
  // pinMode(LEDB, OUTPUT);

  // pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(9600);

  if (!BARO.begin()) {
    Serial.println("Failed to initialize pressure sensor!");
    while (1);
  }

  if (!HTS.begin()) {
    Serial.println("Failed to initialize humidity temperature sensor!");
    while (1);
  }
}

void loop()
{
  float pressure = BARO.readPressure();
  float temperature = HTS.readTemperature();
  float humidity = HTS.readHumidity();

  Serial.print("Pressure = ");
  Serial.print(pressure);
  Serial.println(" kPa");

  Serial.print("Temperature = ");
  Serial.print(temperature);
  Serial.println(" °C");

  Serial.print("Humidity    = ");
  Serial.print(humidity);
  Serial.println(" %");

  Serial.println();

  // wait 1 second to print again
  delay(5000);
}