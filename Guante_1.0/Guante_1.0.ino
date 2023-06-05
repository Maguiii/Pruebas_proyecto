/* Programa MAESTRO
 *  
 *  Este programa esta diseñado para el guante
 *  Se considera la utilizacion de tuch (cuando se activan mandan un HIGH)
 *  
 *  (El pulsador 5 tiene un LOW porque esta conectado a un pulsador)
*/

#define puls1 A0
#define puls2 A1
#define puls3 A2
#define puls4 A3
#define puls5 7


void setup() {
  
  pinMode(puls1, INPUT);
  pinMode(puls2, INPUT);
  pinMode(puls3, INPUT);
  pinMode(puls4, INPUT);
  pinMode(puls5, INPUT);
  
  Serial.begin(57600); // Configura la comunicación serial con el módulo HC-05
}

void loop() {
//TODOS LOS TOUCH FUNCIONAN SOLO CON HIGH NO NECESITAN RESISTENCIAS

  if(digitalRead(puls1) == HIGH){

     Serial.write('1');
     delay(50);
  }
 
  if(digitalRead(puls2) == HIGH){

     Serial.write('2');
     delay(50);
  }
  if(digitalRead(puls3) == HIGH){

     Serial.write('3');
     delay(50);
  }
  if(digitalRead(puls4) == HIGH){

     Serial.write('4');
     delay(50);
  }
  if(digitalRead(puls5) == LOW){ //ESTE PUL ESTA CON LOW PORQUE NO TIENE TOUCH

     Serial.write('5');
     delay(50);
  }

}
