#include <Arduino.h>
#include <Wire.h>
#include "DS1307RTC.h"
#include "Time.h"

#include "TM1637Display.h"

#define CLKPIN 3
#define DIOPIN 2

String dateTimeStr = "";
boolean strFull = false;
tmElements_t dateTime;

TM1637Display display(CLKPIN, DIOPIN);
int8_t ListTime[4]={0,0,0,0};
boolean point=true;

String formatDateTime(tmElements_t &dateTime);
String formatValue(unsigned int nn);

void setup() {
    Serial.begin(9600);

    display.setBrightness(0, true);
}

void loop() {
    if (strFull) {
        // Формат времени для парсинга
        // dd.MM.yyyy HH:mm:ss
        // 01234567890123456789

        dateTime.Hour = dateTimeStr.substring(11,13).toInt();
        dateTime.Minute = dateTimeStr.substring(14,16).toInt();
        dateTime.Second = dateTimeStr.substring(17,19).toInt();
        dateTime.Day = dateTimeStr.substring(0,2).toInt();
        dateTime.Month = dateTimeStr.substring(3,5).toInt();
        dateTime.Year = CalendarYrToTm(dateTimeStr.substring(6,10).toInt());

        RTC.write(dateTime); // записать данные в DS3231

        // очистить строку
        dateTimeStr = "";

        strFull = false;
    }

    // получение данных из ds3231
    if (RTC.read(dateTime)) {

        ListTime[0] = dateTime.Hour/10;
        ListTime[1] = dateTime.Hour%10;
        ListTime[2] = dateTime.Minute/10;
        ListTime[3] = dateTime.Minute%10;

        Serial.println(formatDateTime(dateTime));
    } else {
        Serial.println("error");
        display.clear();
    }

    // вывод времени
    display.showNumberDec(ListTime[0], false, 1, 0);

    // если не использовать условие, то мы не сможем зажигать точки
    if (point)
    {
        uint8_t digitWithPoints = display.encodeDigit(ListTime[1]) ^ 0b10000000;
        display.setSegments(&digitWithPoints, 1, 1);
    } else {
        display.showNumberDec(ListTime[1], false, 1, 1);
    }

    display.showNumberDec(ListTime[2], false, 1, 2);
    display.showNumberDec(ListTime[3], false, 1, 3);

    delay(500);

    // поменять индикацию точек
    point=!point;
}

void serialEvent() {
    while (Serial.available()) {
        char c = (char)Serial.read();

        dateTimeStr += c;

        if (c == '\n')
        {
            strFull = true;
        }
    }
}

String formatDateTime(tmElements_t &datetime){
    String result = "";

    result += formatValue(dateTime.Hour);
    result += ":";
    result += formatValue(dateTime.Minute);
    result += ":";
    result += formatValue(dateTime.Second);
    result += " ";
    result += formatValue(dateTime.Day);
    result += ".";
    result += formatValue(dateTime.Month);
    result += ".";
    result += formatValue(tmYearToCalendar(dateTime.Year));

    return result;
}

String formatValue(unsigned int nn) {
    String result = "";

    if (nn >= 0 && nn < 10)
        result += "0";

    result += String(nn);

    return result;
}