/*
 * PRUEBA MODULO BLUETOOTH ""MAESTRO" 0.0
 * 
 * Prueba inicial de bluetooth, esta emparejada con la prueba bluetooth esclavo 0.0
 *
 * El programa consiste en apretar un pulsador y que se encienda un led
 */


#define pulsador A0 

int dato;


void setup() {
  
  Serial.begin(9600);
  
  pinMode(pulsador, INPUT);
  
}

void loop() {
  
  dato = digitalRead(pulsador);
  if(dato == HIGH){

    Serial.print('1');
  }else
  {
    Serial.print('0');
  }
}
