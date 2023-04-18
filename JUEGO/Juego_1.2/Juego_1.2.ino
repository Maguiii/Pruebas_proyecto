#include <Arduino.h>
/* 
 *  ESTO ES EL JUEGO USANDO EL 74HC595 Y EL I2C DEL LCD
 *  
 *  Este programa trabaja con un pulsador que simula ser un infra
 *  Es la prueba para el proceso de deteccion de un viaje y el llamado a la funcion juego
 *  
 *  FUNCIONA
*/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

int lachtPin = 8;
int clockPin = 13; 
int dataPin = 12;

LiquidCrystal_I2C lcd (0x27,16,2);


#define infra1 A1 //se esta trabajando con un pulsador

volatile int numLed = 0;
volatile int numLedActual = 0;
volatile int activacionJuego = 0;

volatile int aleatorio = 0;
volatile byte myByte = 0;

void juego();


void setup(){

  Serial.begin(9600);

  lcd.init();
  lcd.backlight();
  
  lcd.setCursor(0, 0);
  lcd.print ("  Bienvenido a  ");
  lcd.setCursor(0, 1);
  lcd.print ("  Super Guanti  ");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print ("Una creacion de:");
  lcd.setCursor(0, 1);
  lcd.print ("     M.A.L.     ");
  delay(1000);

  
  pinMode(infra1, INPUT);
  
  pinMode(lachtPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT); 

}

void loop(){
  
  if(digitalRead(infra1) == HIGH){
    delay(300);//esto es para la retencion del pulsador
     juego();
  }
}

void juego(){
/* En aleatorio se guarda el numero que genera la funcion random
 * 
 * myByte esta declarado como byte porque tiene 8 posiciones 
 * 
 * en myByte se guarda un 1 desplazado la cantidad de veces que indique el numero guardado en aleatorio
 * 
 * myByte se manda a la salida y listo
 * 
 * se tiene que usar MSBFIRST para que funcione
 */
  aleatorio = random(0, 5);
  myByte = 0;
  myByte = 1<<aleatorio;
  digitalWrite(lachtPin, LOW); //sube cada 8 ciclos

  shiftOut(dataPin, clockPin, MSBFIRST, myByte);//le mandamos cuatro datos primero la data despues el pin del reloj , el bit menos significativo
  digitalWrite(lachtPin, HIGH);
}
