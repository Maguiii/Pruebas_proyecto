/* 
 *  Esta version tiene implementado el 74hc595 y el i2C del lcd
 *  
 *  JUEGO + CANTDE VIAJES -- No tiene CUENTA REGRESIVA
*/
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

int lachtPin = 8;
int clockPin = 13; 
int dataPin = 12;

LiquidCrystal_I2C lcd (0x27,16,2);

#define incremento 5 
#define inicio 4

#define infra1 A0
#define infra2 A1 
#define infra3 A2 
#define infra4 A3 
#define infra5 0


volatile int numViajes = 0;
volatile int aceptacion = 0;


volatile int flagRegresion = 0;
volatile int contadorViajes = 0;

volatile int activacionJuego = 0; //flag para iniciar el juego
volatile int aleatorio = 0;
volatile byte myByte = 0;

void cantViajes();
void juego();
void finDelJuego();

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
  
  pinMode(incremento, INPUT);
  pinMode(inicio, INPUT);

  pinMode(infra1, INPUT);
  pinMode(infra2, INPUT);
  pinMode(infra3, INPUT);
  pinMode(infra4, INPUT);
  pinMode(infra5, INPUT);


  pinMode(lachtPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT); 
}

void loop(){

  if(aceptacion == 0){ 

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Cant de viajes:");
    cantViajes();
  }
  else{
    
    lcd.setCursor(0,0);
    lcd.print("    A JUGAR!    "); 
    
    if(activacionJuego == 0){
      juego();
    }
    if(digitalRead(infra1) == HIGH || digitalRead(infra2) == HIGH || digitalRead(infra3) == HIGH || digitalRead(infra4) == HIGH || digitalRead(infra5) == HIGH){ 
      delay(300);//retencion del pulsador
      contadorViajes++;
    
      if(contadorViajes < numViajes){
        activacionJuego = 0;
      }
      if(contadorViajes >= numViajes){
        lcd.clear();
        finDelJuego();
      }
    }
  }
}

void cantViajes() { 

  do{

    if(digitalRead(incremento) == HIGH){

      numViajes++; //Esto se podria hacer de 5 en 5
      delay(300); //Este delay hay que sacarlo en un futuro, es para la retencion del pulsador
      lcd.setCursor(0,1);
      lcd.print(numViajes);
    }

  }while(digitalRead(inicio) == LOW);
  
  if(digitalRead(inicio) == HIGH){

    aceptacion = 1;
    lcd.clear(); //el clear esta aca para que se ejecute solo una vez
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
 * 
 * activacionJuego es una flag que se implementa para entrar y salir de la funcion juego y que no se quede el programa trabado en el encendido de los leds
 */
  aleatorio = random(0, 5);
  myByte = 0;
  myByte = 1<<aleatorio;
  
  digitalWrite(lachtPin, LOW); //sube cada 8 ciclos
  shiftOut(dataPin, clockPin, MSBFIRST, myByte);//le mandamos cuatro datos primero la data despues el pin del reloj , el bit menos significativo
  digitalWrite(lachtPin, HIGH);

  activacionJuego = 1;
}

void finDelJuego(){ 

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("  Felicidades!  ");
  lcd.setCursor(0,1);
  lcd.print(" Fin del juego! ");
  delay(2000); //hay que sacar estos delay
 /* lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("   Su tiempo:   ");
  lcd.setCursor(4,1);
  lcd.print(hora); 
  lcd.print(   ":");
  lcd.print(     minnn);
  lcd.print(      ":");
  lcd.print(       seg);//esto deberia imprimir: 00:00:00 (en el centro de la pantalla)
  delay(2000);*/
}
