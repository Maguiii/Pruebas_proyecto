/*
 * Este es el codigo del atmega esclavo
 * 
 * Es el funcionamiento de la grua utilizando 5 pulsadores
 * 
 * El criterio es el siguiente:
 * 
 * boton 1 -- derecha
 * boton 2 -- izquierda
 * boton 3 -- adelante
 * boton 4 -- atras
 * boton 5 -- abajo
 * 
 * la grua esta iniciada en la posicion "arriba", "izquierda", "atras" 
 * con el boton 5 la grua baja, al llegar a la posicion "abajo" (angulo = 0), vuelve a la posicion "arriba" automaticamente
 * 
 */
#include<Servo.h>

Servo miservo_1;
Servo miservo_2;
Servo miservo_3;

volatile int grados1 = 0;
volatile int grados2 = 0;
volatile int grados3 = 90;
volatile int state = 0;
volatile int a = 0;

void setup() {
  
  miservo_1.attach(9, 350, 2900);
  miservo_1.write(grados1); 

  miservo_2.attach(6, 1000, 2000);
  miservo_2.write(grados2); 

  miservo_3.attach(11, 1000, 2000);
  miservo_3.write(grados3);//ESTE TIENE QUE LLEGAR A 30|
  
  Serial.begin(57600); 
}

void loop() {
  if (Serial.available()) { 
    
    state = Serial.read(); 

  ///// SERVO 1 --- DERECHA IZQUIERDA --- 9 --- 180-0 /////
  
    if(state == '1'){
      grados1++;
      if(grados1 >= 180){
        grados1 = 180;
      }
      miservo_1.write(grados1);
      delay(10);
    }
    if(state == '2'){
      grados1--; 
      if(grados1 <= 0){
        grados1 = 0;
      }
      miservo_1.write(grados1);
      delay(10);;
    }

  ///// SERVO 2 --- ADELANTE ATRAS --- 6 --- 180-0 /////
  
    if(state == '3'){
      grados2++;
      

      if(grados2 >= 180){
        grados2 == 180;
      }
      miservo_2.write(grados2);
      delay(10);


     }
      
    if(state == '4'){
      grados2--;

      if(grados2 >= 0){
        grados2 == 0;
      }
      miservo_2.write(grados2);
      delay(10);


    }

  ///// SERVO 3 --- ARRIBA ABAJO --- 11 --- 30-0 /////
  
    if(state == '5'){
      
    grados3--;
      
    if(grados3<=0)
      grados3 = 90;
      
    miservo_3.write(grados3);
    delay(15);
    }
  }
}
