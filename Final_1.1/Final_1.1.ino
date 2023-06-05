/* PROGRAMA ESCLAVO
 *  
 * SE USA PULL UP
 * 
 * NO FUNCIONA
 * 
 * CODIGO CON :
 * - I2C
 * - 74hc595
 * - Infras
 * - Bluetooth 
 * - Servos
 * - Cuenta regresiva
 * 
 * NO TIENE:
 * - Cuenta general
*/

#include <LiquidCrystal_I2C.h>
#include <TimerOne.h>
#include <Wire.h>

//queda libre el pin 2, 12, 13
//0 y 1 son Rx y tx son para el bluetooth

#define infra1 A0
#define infra2 A1
#define infra3 A2
#define infra4 A3
#define infra5 4

#define pinLatch 7  // es la patita SH_CP
#define clockPin 8 // es la patita DS
#define dataPin 5  // A -- data

#define incremento 10
#define inicio 12

#define servo1 9
#define servo2 6
#define servo3 11


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

volatile int state = 0;


void cantViajes();
void cuentaRegresiva();
void juego();
void finDelJuego();

void setup()
{
  Serial.begin(57600); 

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

  pinMode(infra3, INPUT);
  pinMode(infra2, INPUT);
  pinMode(infra3, INPUT);
  pinMode(infra4, INPUT);
  pinMode(infra5, INPUT);

  pinMode(pinLatch, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  pinMode(servo1, OUTPUT);
  pinMode(servo2, OUTPUT);
  pinMode(servo3, OUTPUT);

  digitalWrite(pinLatch, LOW);              
  shiftOut(dataPin, clockPin, MSBFIRST, 0); 
  digitalWrite(pinLatch, HIGH);
  
}

void loop(){

  if(aceptacion == 0) {

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Cant de viajes:");
    cantViajes();
  }
  else 
  { 
    switch (flagRegresion){
      /*
      * flagRegresion se utiliza para ir avanzando en los pasos del programa 
      */
      case 0:
        lcd.setCursor(0, 0);
        lcd.print("El juego inicia");
        lcd.setCursor(0, 1);
        lcd.print("     en: ");
        flagRegresion = 1;
      break;
      case 1:
        /*
        * La funcion cuentaRegresiva empieza a interrumpirse con el timer a partir de ahora
        * 
        * tambien se muestra en pantalla
        */
        Timer1.initialize(1000000); // 1s
        Timer1.attachInterrupt(cuentaRegresiva);

        lcd.setCursor(10, 1);
        lcd.print(regresion);
      break;
      case 2:
        lcd.setCursor(0, 0);
        lcd.print("    A JUGAR!    ");
        lcd.setCursor(0, 1);
        lcd.print("                ");

        if (activacionJuego == 0)
        {
          juego();
          
        }
        //grua
          if (Serial.available()) { 
    
            state = Serial.read(); 
            if(state == '1' || state == '2'){
              digitalWrite(servo1, HIGH);
              delay(5000);
            }
            if(state == '3' || state == '4'){
              digitalWrite(servo2, HIGH);
              delay(5000);
            }
            if(state == '5'){
              digitalWrite(servo3, HIGH);
              delay(5000);
            }
          }
        if (digitalRead(infra3) == LOW || digitalRead(infra5) == LOW || digitalRead(infra4) == LOW || digitalRead(infra2) == LOW || digitalRead(infra1) == LOW)
        {
          delay(500); // retencion del pulsador
          contadorViajes++;

          if (contadorViajes < numViajes)
          {
            activacionJuego = 0;
          }
          if (contadorViajes >= numViajes)
          {
            lcd.clear();
            flagRegresion = 3;
          }
        }
        
        
      break;
      case 3:
        finDelJuego();
      break;
    }
  }
}
void cantViajes(){
  /* Al pulsar el boton de incremento se aumenta la cantidad de viajes
   *
   * Si se pulsa el boton inicio se termina la configuracion de cantidad de viajes e inicia la cuenta regresiva
  */
  while(digitalRead(inicio) == HIGH){
    if(digitalRead(incremento) == LOW){
      delay(300);

      numViajes++;
      lcd.setCursor(0,1);
      lcd.print(numViajes);
    } 
  }

  if (digitalRead(inicio) == LOW) {
    delay(300);
    aceptacion = 1;
    lcd.clear(); //el clear esta aca para que se ejecute solo una vez
  }
}
void juego() {
  /* 
   * Genera un numero aleatorio, el cuel no puede ser igual al anterior
   * 
   * Dependiendo de ese numero se marca que salida debe tener el 74hc595
   * 
   * Los numeros en binario tienen un unico cero dentro de los primeros 5 digitos
   * 
   * Se ulizan las salidas QA, QB, QC, QD, QE del 74hc595
   * 
   * activacionJuego es una flag que se modifica para salir de la funcion juego y volver al codigo principal
  */
  do{
    aleatorio = random(0, 5);
  }while(aleatorio == numAnterior);
  
  switch (aleatorio)
  {
    case 0:
      digitalWrite(pinLatch, LOW);              
      shiftOut(dataPin, clockPin, MSBFIRST, 1); 
      digitalWrite(pinLatch, HIGH);
      numAnterior = 0;
      activacionJuego = 1;
    break;
    case 1:
      digitalWrite(pinLatch, LOW);              
      shiftOut(dataPin, clockPin, MSBFIRST, 2); 
      digitalWrite(pinLatch, HIGH);
      numAnterior = 1;
      activacionJuego = 1;
    break;
    case 2:
      digitalWrite(pinLatch, LOW);              
      shiftOut(dataPin, clockPin, MSBFIRST, 4); 
      digitalWrite(pinLatch, HIGH);
      numAnterior = 2;
      activacionJuego = 1;
    break;
    case 3:
      digitalWrite(pinLatch, LOW);              
      shiftOut(dataPin, clockPin, MSBFIRST, 8);
      digitalWrite(pinLatch, HIGH);
      numAnterior = 3;
      activacionJuego = 1;
    break;
    case 4:
      digitalWrite(pinLatch, LOW);               
      shiftOut(dataPin, clockPin, MSBFIRST, 16); 
      digitalWrite(pinLatch, HIGH);
      numAnterior = 4;
      activacionJuego = 1;
    break;
  }
}
void cuentaRegresiva()
{
  /* Esto funciona de forma interrumpida por el Timer1 cada 1seg
   *
   * regresion sera la cuenta propiamente dicho
   * cuando llegue a 0 se cambiara flagRegresion y ya no se volvera a esta funcion (se utiliza <=0 porque sino empieza a mostrar numeros negativos)
  */
  regresion = 5 - (aux++);

  if (regresion <= 0)
  {
    flagRegresion = 2;
  }
}
void finDelJuego(){

/*Es el mensaje que se mostrara al finalizar el juego
  
  Aca tambien se pueden agregar para mostrar la cantidad de veces que se toco cada dedo y la cuenta general
*/
  digitalWrite(pinLatch, LOW);              
  shiftOut(dataPin, clockPin, MSBFIRST, 0); 
  digitalWrite(pinLatch, HIGH);
  
  lcd.setCursor(0, 0);
  lcd.print("  Felicidades!  ");
  lcd.setCursor(0, 1);
  lcd.print(" Fin del juego! ");
}
/*
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
void arriba(){
  grados2++;
  
  if(grados2 >= 180){ 
    grados2 = 180;
  }
  
  miservo_2.write(grados2);
  delay(10);
  miservo_3.write(grados2);
  delay(10);
}
void abajo(){
  grados2--;
  
  if(grados2 <= 0){ 
    grados2 = 0;
  }
  
  miservo_2.write(grados2);
  delay(10);
  miservo_3.write(grados2);
  delay(10);
}
}*/
