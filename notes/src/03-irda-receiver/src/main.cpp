#include <Arduino.h>
#include <IRremote.h>

IRrecv irrecv(3);

decode_results results;

void setup(){
  Serial.begin(9600);
  irrecv.enableIRIn(); // запускаем прием
}

void loop(){
  if (irrecv.decode(&results)) { // если данные пришли
    
    Serial.println( results.value, HEX ); // выводим полученное значение

    switch ( results.value ) {
        case 0x20DF40BF:
            digitalWrite( 13, HIGH );
            break;
        case 0x20DFC03F:
            digitalWrite( 13, LOW );
            break;
    }

    irrecv.resume(); // принимаем следующую команду
  }
}