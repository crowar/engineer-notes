#include <Arduino.h>

#include <SPI.h>
#include "SD.h"

const uint8_t csPin = 4;
const String fileName = "TEMP.TXT";

File file;

void setup(){

  Serial.begin(9600);

  // ожидаем соединения
  while(!Serial){;}

  if(!SD.begin(csPin)){
    Serial.println("SD-card not found");
    return;
  }

  if(SD.exists(fileName)){
    Serial.println("=> file exist");
  }else{
    Serial.println("=> file doesn't exist");
  }

  file = SD.open(fileName, FILE_WRITE);
  file.println("Line");

  if (file){
    file.close();
  }
}

void loop(){

}