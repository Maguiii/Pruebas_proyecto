//PROGRAMA TESTEO DE CONSUMO DE SERVOS
#include <SoftwareSerial.h>
#include<Servo.h>

#define puls1 A1
#define puls2 A4

Servo miservo_1;
Servo miservo_2;
Servo miservo_3;

volatile int grados1 = 0;
volatile int grados2 = 0;
volatile int grados3 = 0;
volatile int state = 0;

void setup() {
  
  miservo_1.attach(9, 350, 2900); // EL 2 ES EL PIN DONDE ESTA CONECTADO EL 750 ES EL 0 Y EL 1800 POR LOS 180°
  miservo_1.write(grados1);//b

  miservo_2.attach(6, 1000, 2000);
  miservo_2.write(grados2);

  miservo_3.attach(11, 1000, 2000); // EL 2 ES EL PIN DONDE ESTA CONECTADO EL 750 ES EL 0 Y EL 1800 POR LOS 180°
  miservo_3.write(grados3);//b 
  
  Serial.begin(57600); // Configura la comunicación serial con el módulo HC-05
}

void loop() {


    if(digitalRead(puls1) == HIGH){
  
      grados1++;
      grados2++;
      grados3++;
      if(grados3<=30){
        grados3 = 30;
      }
      
      
      miservo_1.write(grados1);
      delay(10);
      miservo_2.write(grados2);
      delay(10);
      miservo_3.write(grados3);
      delay(10);
     }
    if(digitalRead(puls2)== HIGH){
  
      grados1--;
      grados2--;
      grados3--;

      miservo_1.write(grados1);
      delay(10);
      miservo_2.write(grados2);
      delay(10);
      miservo_3.write(grados3);
      delay(10);
    }
}
    
