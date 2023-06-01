/* 
 *  Este es el codigo del atmega esclavo
 *  
 *  Es el funcionamiento de la grua utilizando 5 pulsadores
 *  
 *  La diferencia al servo_1.0 es que este utiliza la funcion switch y que no tiene mas velocidad el servo2
*/
#include<Servo.h>
#include <VarSpeedServo.h>

VarSpeedServo miservo_2;

Servo miservo_1;
Servo miservo_3;

int grados1 = 0;
int grados2 = 0;
int grados3 = 90;
int state = 0;

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
  if (Serial.available()) { 
    
    state = Serial.read(); 

    switch(state){
      ///SERVO 1 -- DERECHA IZQUIERDA -- 9///
      case '1':
        grados1++;
        if(grados1 >= 180)
          grados1 = 180;
      
        miservo_1.write(grados1);
        delay(10);
      break;
      case '2':
        grados1--; 
        if(grados1 <= 0)
          grados1 = 0;
      
        miservo_1.write(grados1);
        delay(10);
      break;
      
      ///SERVO 2 -- ADELANTE ATRAS -- 6///
      case '3':
        grados2++;
        if(grados2 >= 180)
          grados2 == 180;
   
        miservo_2.write(grados2, 255, false);
        delay(10);
      break;
      case '4':
        grados2--;
        if(grados2 >= 0)
          grados2 == 0;
       
        miservo_2.write(grados2, 255, false);
        delay(10);
      break;
      
      ///SERVO 3 -- ABAJO -- 11///
      case '5':
        grados3--;
        if(grados3<=0) // if(grados3<=0 || (digitalRead(infra1)== HIGH)|| (digitalRead(infra2)== HIGH)|| (digitalRead(infra3)== HIGH)|| (digitalRead(infra4)== HIGH)|| (digitalRead(infra5)== HIGH)){} 
          grados3 = 90;
          
        miservo_3.write(grados3);
        delay(15);
      break;
    }
  }
}
