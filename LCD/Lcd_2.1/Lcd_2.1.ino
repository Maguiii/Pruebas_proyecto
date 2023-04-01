#include <LiquidCrystal.h>

/*PRUEBA JUEGO 1.0
 * 
 * Consiste en la generacion de un num random y 
 * el encendido del led correspondiente a ese numero
 * 
 * 
*/

#define pulsador 4
#define led1 8
#define led1 9
#define led1 10
#define led1 11
#define led1 12

LiquidCrystal lcd(12, 11, 10, 9, 8, 7);


volatile int numLedActual = 0;
volatile int numLed = 0;

void juego();


void setup() {
  lcd.begin(16, 2);
  
  /*Mensaje de Bienvenida*/
  //lcd.blink(); Esto esta comentado porque trae problemas cuando en el proteus aparece "Inicio del juego", habria que ver si en el maletin pasa lo mismo o no
  //delay(1000);
/*lcd.setCursor(0, 0);
  lcd.print ("  Bienvenido a  ");
  lcd.setCursor(0, 1);
  lcd.print ("  Super Guanti  ");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print ("Una creacion de:");
  lcd.setCursor(0, 1);
  lcd.print ("     M.A.L.     ");
  delay(1000);  //Aca se usa un delay no se si vale la pena sacarlo
*/
  pinMode (led1, OUTPUT);
  pinMode (led2, OUTPUT);
  pinMode (led3, OUTPUT);
  pinMode (led4, OUTPUT);
  pinMode (led5, OUTPUT);

  pinMode (pulsador, INPUT);
}

void loop() {
  
  if(digitalRead(pulsador) == HIGH){
    juego()
  }
}
void juego(){
  
  do{
    numLed = random(1, 5);
    
  }while(numLed != numLedActual);

  
  switch(numLed)
  case 1:
    digitalWrite(led1, HIGH);
    numLedActual = 1;
  break;
  case 2:
    digitalWrite(led2, HIGH);
    numLedActual = 2;
  break;
  case 3:
    digitalWrite(led3, HIGH);
    numLedActual = 3;
  break;
  case 4:
    digitalWrite(led4, HIGH);
    numLedActual = 4;
  break;
  case 5:
    digitalWrite(led5, HIGH);
    numLedActual = 5;
  break;
}
