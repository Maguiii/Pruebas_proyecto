/*
 * 
*/


#include <LiquidCrystal_I2C.h>
#include <TimerOne.h>
#include <Servo.h>


#define incremento 10
#define inicio 11

Servo miservo_1; // servo 1 derecha izquierda
Servo miservo_2; // Servo 2 y 3 hacen lo msimo por que es para estabilizacion
Servo miservo_3; // servo 2 y 3 arriab y atras

LiquidCrystal_I2C lcd(0x3F, 16, 2); //Va conectado al A5 y al A4

volatile int numViajes = 0;
volatile int aceptacion = 0;

volatile int flagRegresion = 0;
volatile int contadorViajes = 0;
volatile int numAnterior = 0;

volatile int activacionJuego = 0; // flag para iniciar el juego
volatile int aleatorio = 0;

volatile int regresion;
volatile int aux = 0;

volatile int grados1 = 0;
volatile int grados2 = 0;
volatile int grados3 = 0;
volatile int state = 0;

volatile int seg = 0;
volatile int mins = 0;
volatile int hs = 0;

volatile int flagFinal = 0;

volatile int indice = 0;
volatile int anular = 0;
volatile int mayor = 0;
volatile int menique = 0;


void cantViajes();
void cuentaRegresiva();
void juego();
void finDelJuego();
void conteoGeneral();

void derecha(); //servo 1 -- 9
void izquierda();
void adelante();
void atras();

void setup()
{
  Serial.begin(9600);

  lcd.init();
  lcd.backlight();
  //Mensaje de bienvenida
  lcd.setCursor(0, 0);
  lcd.print("  Bienvenido a  ");
  lcd.setCursor(0, 1);
  lcd.print("  Super Guanti  ");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Una creacion de:");
  lcd.setCursor(0, 1);
  lcd.print("     M.A.L.     ");
  delay(1000);

  pinMode(incremento, INPUT);
  pinMode(inicio, INPUT);


  miservo_1.attach(9, 350, 2900);
  miservo_1.write(grados1); 

  miservo_2.attach(6, 1000, 2000);
  miservo_2.write(grados2); 

  miservo_3.attach(11, 1000, 2000);
  miservo_3.write(grados3);//ESTE TIENE QUE LLEGAR A 30|

  Serial.begin(57600); 
}

void loop(){

  if(aceptacion == 0) {

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Cant de viajes:");
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("eligiendo...");
    delay(5000);
    aceptacion = 1;
  }
  else 
  {
    switch (flagRegresion){
      
      case 0:
        lcd.setCursor(0, 0);
        lcd.print("El juego inicia");
        lcd.setCursor(0, 1);
        lcd.print("     en: ");
        flagRegresion = 1;
      break;
      case 1:
       
        lcd.setCursor(10, 1);
        lcd.print("cuenta reg");
        flagRegresion = 2;
      break;
      case 2:
        lcd.setCursor(0, 0);
        lcd.print("    A JUGAR!    ");
        lcd.setCursor(0, 1);
        lcd.print("                ");

        

        if (activacionJuego == 0)
        {
          if (Serial.available() > 0){

          state = Serial.read();
          Serial.write(state);
        }

        if (state == '1'){
          derecha();
          state = 0;
          indice++;
        }
        if (state == '2'){
          izquierda();
          state = 0;
          anular++;
        }
        if (state == '3'){
          adelante();
          state = 0;
          mayor++;
        }
        if (state == '4'){
          atras();
          state = 0;
          menique++;
        }
          lcd.clear(),
          lcd.setCursor(0, 0);
          lcd.print("Juego");


        }
        else{
            
            lcd.clear();
            lcd.print("fin");
            delay(5000);
          }
        
        break;
        }
    }
  }




void derecha(){
  grados1++;

  if(grados1 >= 180){  
    grados1 = 180;
  }
  
  miservo_1.write(grados1);
  delay(10);
}
void izquierda(){
  grados1--;
  
  if(grados1 <= 0){ 
    grados1 = 0;
  }
  
  miservo_1.write(grados1);
  delay(10);
}
void adelante(){
  grados2++;
  
  if(grados2 >= 180){ 
    grados2 = 180;
  }
  
  miservo_2.write(grados2);
  delay(10);
}
void atras(){
  grados2--;
  
  if(grados2 <= 0){ 
    grados2 = 0;
  }
  
  miservo_2.write(grados2);
  delay(10);
}
