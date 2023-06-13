#include <Servo.h>

Servo miservo_1;
Servo miservo_2;
Servo miservo_3;

volatile int grados1 = 0;
volatile int grados2 = 0;
volatile int grados3 = 0;

volatile byte estadoBluetooth = 0;


void setup() {

  //set timer2 interrupt every 128us
TCCR2A = 0;// set entire TCCR2A register to 0
TCCR2B = 0;// same for TCCR2B
TCNT2 = 0;//initialize counter value to 0
// set compare match register for 7.8khz increments
OCR2A = 255;// = (16*10^6) / (7812.5*8) - 1 (must be <256)
// turn on CTC mode
TCCR2A |= (1 << WGM21);
// Set CS11 bit for 8 prescaler
TCCR2B |= (1 << CS11);//////////////////////CS21   CS20  EN 1
// enable timer compare interrupt
TIMSK2 |= (1 << OCIE2A);



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

        ///SERVO 1 -- DERECHA IZQUIERDA -- 9/// COPIAR ESTO PARA TODAS LAS INSTRUCCIONES DE SERVO
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
        
         
      }
}
