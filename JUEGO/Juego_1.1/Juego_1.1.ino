#include <LiquidCrystal.h>

/*PRUEBA JUEGO 1.0
 * 
 * Consiste en la generacion de un num random y 
 * el encendido del led correspondiente a ese numero
 * 
 * EN ESTA VERSION 
 * 
 * Los numeros generados con random son mostrados en el lcd
*/

#define pulsador 4

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

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("esta funcionando");

  pinMode (pulsador, INPUT);
}

void loop() {

  if(digitalRead(pulsador) == LOW){
    delay(300);
    juego();
  }
}

void juego(){
  
  numLed = random(1, 5);
 
  switch(numLed){
    case 1:
      lcd.print(1);
    break;
    case 2:
      lcd.print(2);
    break;
    case 3:
      lcd.print(3);
    break;
    case 4:
      lcd.print(4);
    break;
    case 5:
      lcd.print(5);
    break;
  }
}
