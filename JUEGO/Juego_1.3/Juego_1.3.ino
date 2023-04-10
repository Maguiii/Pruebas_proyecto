/* 
 *  Esta es la parte del codigo que hace funcionar a la funcion juego con el 74hc595
 *  
*/
int lachtPin = 8;
int clockPin = 13; 
int dataPin = 12;
byte myByte = 0;

void setup() {

  Serial.begin(9600);
  
  pinMode(lachtPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

}

void loop() {
/* En aleatorio se guarda el numero que genera la funcion random
 * 
 * myByte esta declarado como byte porque tiene 8 posiciones 
 * 
 * en myByte se guarda un 1 desplazado la cantidad de veces que indique el numero guardado en aleatorio
 * 
 * myByte se manda a la salida y listo
 * 
 * se tiene que usar MSBFIRST para que funcione
 * 
 */

  int aleatorio =random(0, 5);
  myByte = 0;
  myByte = 1<<aleatorio;
  digitalWrite(lachtPin, LOW); //sube cada 8 ciclos

  shiftOut(dataPin, clockPin, MSBFIRST, myByte);//le mandamos cuatro datos primero la data despues el pin del reloj , el bit menos significativo
  digitalWrite(lachtPin, HIGH);
  delay(300);

}
