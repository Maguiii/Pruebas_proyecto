#include <Servo.h>

Servo miservo_1;
Servo miservo_2;
Servo miservo_3;

volatile int grados1 = 0;
volatile int grados2 = 0;
volatile int grados3 = 90;

volatile byte estadoBluetooth = 0;


void setup() {

  Serial.begin(57600); 

  miservo_1.attach(9, 350, 2900); //servo base, derecha-izquierda
  miservo_1.write(grados1); 

  miservo_2.attach(6, 1000, 2000); //servo de la derecha, adelante-atras
  miservo_2.write(grados2); 

  miservo_3.attach(11, 1000, 2000); //servo de la izqueirda, abajo
  miservo_3.write(grados3);
  delay(500);
  
}

void loop() {
  if (Serial.available()){

        estadoBluetooth = Serial.read(); 

        ///CONDICION 0 CUANDO NO SE ESTA PULSANDO NADA ///
        if(estadoBluetooth == '0'){
          miservo_1.write(grados1);
          miservo_2.write(grados2);
          miservo_3.write(grados3);
        }

        ///SERVO 1 -- DERECHA IZQUIERDA -- 9///
        if(estadoBluetooth == '1'){
          grados1++;
          if(grados1 >= 180){
            grados1 = 180;
          }
          miservo_1.write(grados1); //,0 para velocidad 
        }

        if(estadoBluetooth == '3'){
          grados1--;
          if(grados1 <= 0){
            grados1 = 0;
          }
          miservo_1.write(grados1);
        }
        ///SERVO 2 -- ADELANTE ATRAS -- 6///
        if(estadoBluetooth == '5'){
          grados2++;
          if(grados2 >= 180){
            grados2 = 180;
          }
          miservo_2.write(grados2);
        }

        if(estadoBluetooth == '7'){
          grados2--;
          if(grados2 <= 0){
            grados2 = 0;
          }
          miservo_2.write(grados2);
        }
        ///SERVO 3 -- ABAJO -- 11///
        if(estadoBluetooth == '9'){    
          grados3--;        
          if(grados3<=0){
            grados3 = 90;
          }
          miservo_3.write(grados3);
        }  
      }
}
