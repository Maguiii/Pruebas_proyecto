#include <VarSpeedServo.h>

/*
 * Este es el codigo del atmega esclavo
 * 
 * Es el funcionamiento de la grua utilizando 5 pulsadores 
 * Tambien tiene la velocidad aumentada del servo 2 (adelante, atras)
 * 
 * El criterio es el siguiente:
 * 
 * boton 1 -- derecha
 * boton 2 -- izquierda
 * boton 3 -- adelante
 * boton 4 -- atras
 * boton 5 -- abajo
 * 
 * La grua esta iniciada en la posicion "arriba", "izquierda", "atras" 
 * Con el boton 5 la grua baja, al llegar a la posicion "abajo" (angulo = 0), vuelve a la posicion "arriba" automaticamente
 * 
 */

VarSpeedServo miservo_1, miservo_2, miservo_3;

volatile int grados1 = 0;
volatile int grados2 = 0;
volatile int grados3 = 110;
volatile int state = 0;


void setup() {
  
  miservo_1.attach(9, 350, 2900); //servo base, derecha-izquierda
  miservo_1.write(grados1); 

  miservo_2.attach(6, 1000, 2000); //servo de la derecha, adelante-atras
  miservo_2.write(grados2); 

  miservo_3.attach(11, 1000, 2000); //servo de la izqueirda, abajo
  miservo_3.write(grados3);
  
  Serial.begin(57600); 
}

void loop() {
  
  int rapido = 200;
  int normal = 0;
  if (Serial.available()) { 
    
    state = Serial.read(); 

    ///SERVO 1 -- DERECHA IZQUIERDA -- 9///
  
    if(state == '1'){
      grados1++;
      if(grados1 >= 180){
        grados1 = 180;
      }
      
      miservo_1.write(grados1, normal);
      delay(10);
    }
    if(state == '2'){
      grados1--; 
      if(grados1 <= 0){
        grados1 = 0;
      }
      
      miservo_1.write(grados1, normal);
      delay(10);
    }

    ///SERVO 1 -- DERECHA IZQUIERDA -- 9///
 
    if(state == '3'){
      grados2++;
      if(grados2 >= 180){
        grados2 == 180;
      }
      
      miservo_2.write(grados2, normal);
      delay(10);
    }
    if(state == '4'){
      grados2--;
      if(grados2 >= 0){
        grados2 == 0;
      }
      
      miservo_2.write(grados2, normal);
      delay(10);
    }

    ///SERVO 3 -- ABAJO -- 11///
  
    if(state == '5'){    
      grados3--;        
      if(grados3<=0){
        grados3 = 90;
      }
        
      miservo_3.write(grados3, rapido);
      delay(15);
    }
  }
}
