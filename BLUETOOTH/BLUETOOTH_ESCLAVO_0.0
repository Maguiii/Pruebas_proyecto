#include <Arduino.h>

/*
 * PRUEBA MODULO BLUETOOTH "ESCLAVO" 0.0
 * 
 * Prueba inicial de bluetooth, esta emparejada con la prueba bluetooth maestro 0.0
 *
 * El programa consiste en apretar un pulsador y que se encienda un led
 */


#define led 4

int state;


void setup() {
  
  Serial.begin(9600);
  
  pinMode(led, OUTPUT);
  
}

void loop() {
  
   if(Serial.available() > 0){
    
    state = Serial.read();
   }

   if(state == '1'){
    digitalWrite(led, HIGH);
   }
   if(state == '0'){
    digitalWrite(led, LOW);
   }
}
