# Arduino Nano 33 BLE

Краткое описание платы можно подсмотреть на [официальном сайте](https://store.arduino.cc/usa/nano-33-ble-sense-with-headers)

|Наименование|Модель|I2C адрес|
|---|---|---|
|Microcontroller|nRF52840 ([datasheet](https://content.arduino.cc/assets/Nano_BLE_MCU-nRF52840_PS_v1.1.pdf))||
|IMU|LSM9DS1 ([datasheet](https://content.arduino.cc/assets/Nano_BLE_Sense_lsm9ds1.pdf), [library](https://github.com/arduino-libraries/Arduino_LSM9DS1.git))|0x6b|
|Microphone|MP34DT05 ([datasheet](https://content.arduino.cc/assets/Nano_BLE_Sense_mp34dt05-a.pdf), [library](https://github.com/arduino-libraries/ArduinoSound.git))||
|Gesture, light, proximity|APDS9960 ([datasheet](https://content.arduino.cc/assets/Nano_BLE_Sense_av02-4191en_ds_apds-9960.pdf), [library](https://github.com/arduino-libraries/Arduino_APDS9960.git))|0x39|
|Barometric pressure|LPS22HB ([datasheet](https://content.arduino.cc/assets/Nano_BLE_Sense_lps22hb.pdf), [library](https://github.com/arduino-libraries/Arduino_LPS22HB.git))|0x5C|
|Temperature, humidity|HTS221 ([datasheet](https://content.arduino.cc/assets/Nano_BLE_Sense_HTS221.pdf), [library](https://github.com/arduino-libraries/Arduino_HTS221.git))|0x5F|

## Светодиоды на борту

На плате имеется RGB светодиод, каждый цвет подключен к собственному пину

```text
Red - 22
Green - 23
Blue - 24
```

> Не следуется забывать про светодиод работающий на 13 пине

## Подключение по USB

Используемый чип NINA B306 (nRF52840) имеет свой собственный USB - это позволяет устройству выступароль в роли клиентского USB устройства (клавиатура, мышка и т.д.)

Чип поддерживает работу по USB 2.0 с полноценной передачей на скоросте 12 Mbps
