#include <Arduino.h>

#include <Servo.h>

/* Programa paral probar los servos
 * 
 * tiene 4 pulsadores que menejan a los servos
 * 
 * esta pensado para configurar bien las funciones de los servos antes de agregarle el bluetooth
*/

Servo miservo_1; // servo 1 derecha izquierda
Servo miservo_2; //Servo 2 y 3 hacen lo msimo por que es para estabilizacion
Servo miservo_3;//servo 2 y 3 arriab y abajo 

#define pulsador1 A0
#define pulsador2 A1
#define pulsador3 A2
#define pulsador4 A3

volatile int grados = 90;

void derecha();
void arriba();
void abajo();
void izquierda();

void setup() {

  Serial.begin(9600);
  
  miservo_1.attach(3,750,1800); // EL 2 ES EL PIN DONDE ESTA CONECTADO EL 750 ES EL 0 Y EL 1800 POR LOS 180°
  miservo_1.write(grados);

  miservo_2.attach(5,750,1800); // EL 2 ES EL PIN DONDE ESTA CONECTADO EL 750 ES EL 0 Y EL 1800 POR LOS 180°
  miservo_2.write(grados);

  miservo_3.attach(6,750,1800); // EL 2 ES EL PIN DONDE ESTA CONECTADO EL 750 ES EL 0 Y EL 1800 POR LOS 180°
  miservo_3.write(grados);

}

void loop() {

  if(pulsador1 == HIGH){
    derecha();
  }
  if(pulsador2 == HIGH){
    izquierda();
  }
  if(pulsador3 == HIGH){
    arriba();
  }
  if(pulsador4 == HIGH){
    abajo();
  }
  
}
void derecha(){

  grados++;
  if(grados >= 180){ // Protege el sero de no sobreexigirlos 

    grados = 180;
  } 
  miservo_1.write(grados);
  delay(10);

}
void izquierda(){

  grados--;
  if(grados <= 0){ //Protege el servo

    grados = 0;
  }
  miservo_1.write(grados);
  delay(10);
}
void arriba(){
  
  grados++;
  if(grados >= 180){ // Protege el sero de no sobreexigirlos 
  
    grados = 180;
  }
  miservo_2.write(grados);
  delay(10);
  
  miservo_3.write(grados);
  delay(10);
}
void abajo(){

  grados--;
  if(grados <= 0){ //Protege el servo

    grados = 0;
  }
  miservo_2.write(grados);
  delay(10);
  
  miservo_3.write(grados);
  delay(10);
}
