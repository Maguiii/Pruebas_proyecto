/* Programa paral el atmega esclavo
 * 
 * Tiene la deteccion del otro bluetooth y los servos estan simulados con leds
 * 
 * No esta probado
*/
#define led_abajo 5
#define led_arriba 6
#define led_izquierda 7
#define led_derecha 8

volatile int state = 0;

void derecha();
void arriba();
void abajo();
void izquierda();

void setup() {

  Serial.begin(9600);

  pinMode(led_arriba, OUTPUT);
  pinMode(led_abajo, OUTPUT);
  pinMode(led_izquierda, OUTPUT);
  pinMode(led_derecha, OUTPUT);

}

void loop() {

  if(Serial.available() > 0){
    
    state = Serial.read();
  }

//No estoy segura si este switch va a funcionar como los if 
  switch(state){
    case '1':
      derecha();
    break;
    case '2':
      izquierda();
    break;
    case '3':
      arriba(); 
    break;
    case '4':
      abajo();
    break;
  }
  
}
void derecha(){

  digitalWrite(led_derecha, HIGH);
}
void izquierda(){

  digitalWrite(led_izquierda, HIGH);
}
void arriba(){
  
  digitalWrite(led_arriba, HIGH);
}
void abajo(){

  digitalWrite(led_abajo, HIGH);
}
