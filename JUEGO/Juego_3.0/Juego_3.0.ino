#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#include <TimerOne.h>

/*PRUEBA LCD 2.0
 * 
 * Consiste en el texto inicial (aparecera al prender el proyecto),
 * el texto que dara inicio a la configuracion (cuando el usuario elige la cantidad de viajes) 
 * la cuenta regresiva antes del inicio del juego
 * el juego (el pulsador en A5 simula ser un infra)
 * el texto de finalizacion del juego
 * 
 * ESTA VERSION
 * 
 * Tiene la implementacion del 74hc595 y del lcd I2C
 * 
*/

#define incremento 5 //Estos pines los puse por el proteus 
#define inicio 4
#define infra A5 //en realidad va a ser un pulsador

#define lachtPin = A0;
#define clockPin = A1; 
#define dataPin = A2;

LiquidCrystal_I2C lcd (0x27,16,2);

volatile int numViajes = 0;
volatile int aceptacion = 0;

volatile int flagRegresion = 0;
volatile int aux = 0;

volatile int activacionJuego = 0; //flag para iniciar el juego
volatile int numLed = 0;
volatile int numLedActual = 0;

int regresion;
int contadorViajes;

void cantViajes();
void cuentaRegresiva();
void juego();
void finDelJuego();

void setup() {
  lcd.begin(16, 2);
  
  /*Mensaje de Bienvenida*/
  //lcd.blink(); Esto esta comentado porque trae problemas cuando en el proteus aparece "Inicio del juego", habria que ver si en el maletin pasa lo mismo o no
  //delay(1000);
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
  delay(1000);  //Aca se usa un delay no se si vale la pena sacarlo

  pinMode(incremento, INPUT_PULLUP);
  pinMode(inicio, INPUT_PULLUP);
  pinMode(infra, INPUT);

  pinMode(latchPin, OUTPUT);
  pinMode(clckPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}

void loop() {
  /*Inicia el programa y se configura la cantidad de viajes que se van a realizar 
   * Se incrementa la cantidad de viajes con el boton incremento (esto sucede el la funcion cantViajes() )
   * se frena ese proceso y se da inicio al juego con el boton inicio (lo que sucede en el else)
   * 
   * aceptacion es una bandera que se activa con el boton de inicio y que se utiliza para que la configuracion de la 
   * cantidad de viajes solo se produzca al inicio del programa 
   * 
   * numViajes guarda la cantidad de viajes configurados
   */

  if(aceptacion == 0){ 
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Cant de viajes:");
    cantViajes();
  }
  else{  
    /* Finalizada la configuracion 
     * Inicia el juego con una cuenta regresiva de 5 seg, al llegar al final inicia el juego en si
     *  
     * flagRegresion es una bandera con cuatro estados 
     *    - estado inicial (0) permite que se lea "El juego inicia en: " 
     *                         nunca se vuelve a este estado, por eso nunca se vuelve a mostrar "El juego inicia en: "
     *                         
     *    - segundo estado (1) Inicia la interrupcion por timmer de la funcion cuenta regresiva 
     *    
     *    - tercer estado (2)  se establece al termina la cuenta regresiva
     *                         es en este estado que puede dar comienzo el juego
    */
    switch(flagRegresion){
      case 0:
        lcd.setCursor(0,0);
        lcd.print("El juego inicia");
        lcd.setCursor(0,1);
        lcd.print("     en: ");
        flagRegresion = 1;
      break;
      case 1:
        Timer1.initialize(1000000);//1s
        Timer1.attachInterrupt(cuentaRegresiva);
      break;
      case 2:
        lcd.setCursor(0,0);
        lcd.print("    A JUGAR!    "); 

        /* Se utiliza la flag activacionJuego para poder entrar y salir de la funcion juego
         *  (sino se usa el programa se queda en el loop juego infinitamente)
         *  
         *  Cuando un infra detecta que se realizo un viaje, la variable contadorViajes aumenta
         *  esta variable es comparada con numViajes
         *    - si es menor se vuelve a activar el juego (en el caso de que sean iguales el juego no se volvera a activar 
         *      (si se volviera a activar, se encenderia otro led lo cual seria un viaje de mas)
         *    - si es igual finaliza el juego
         * 
         *  
        */

        if(activacionJuego == 0){
          juego();
        }
        if(digitalRead(infra) == LOW){ //Aca falta agregar una retencion para el pulsador
          contadorViajes++;
          
          if(contadorViajes < numViajes){
            activacionJuego = 0;
          }
          if(contadorViajes >= numViajes){
            lcd.clear();
            finDelJuego();
          }
        }
      break;
    }
  }
}

void cantViajes(){ 
  /*Esta funcion sirve para que el usuario elija la cantidad de viajes que desea realizar, 
   * para hacerlo se cuenta con un pulsador(incremento) 
   * el resultado se guarda en la variable global numViajes 
   * 
   * cuando se activa el boton inicio, se termina el incremento y se cambia el estado de la bandera aceptacion 
   */
  do{
    if(digitalRead(incremento) == LOW){
      numViajes++; //Esto se podria hacer de 5 en 5
      delay(300); //Este delay hay que sacarlo en un futuro, es para la retencion del pulsador
      lcd.setCursor(0,1);
      lcd.print(numViajes);
    }
  }while(digitalRead(inicio) == HIGH);
  
  if(digitalRead(inicio) == LOW){
    aceptacion = 1;
    lcd.clear(); //el clear esta aca para que se ejecute solo una vez
  }
}
void cuentaRegresiva(){
  /* Esto funciona de forma interrumpida por el Timer1 cada 1seg
   *
   * regresion sera la cuenta propiamente dicho 
   * cuando llegue a 0 se cambiara flagRegresion y ya no se volvera a esta funcion (se utiliza <=0 porque sino empieza a mostrar numeros negativos)
  */
  regresion = 3 - (aux++);
  lcd.setCursor(10,1);
  lcd.print(regresion);

  if(regresion <= 0){
    lcd.clear(); //El clear esta aca para que no se repita y el "A JUGAR!" titile
    flagRegresion = 2;
  }
}
void juego(){
/* Esta funcion se encarga de encender los leds del juego
 *  
 * Se genera un numero aleatorio entre el 1 y el 5 y despues se prende el led correspondiente
 * No se deberian prender dos consecutivas el mismo led
 * 
 * Al encenderse un led, se actualiza la variable numLedActual, que indica el led que esta prendido y se cambia el estado de activacionJuego
 * es una flag la cual no permitira que se acceda a esta funcion hasta que algun infra detecte que el viaje se completo
 *  
*/
  do{
    numLed = random(1, 16);
  }while(numLed == numLedActual && (numLed != 1 || numLed != 2 || numLed != 8 || numLed != 16));
  
  digitalWrite(lachtPin, LOW); //La subida de datos esta desactivada
  shiftOut(dataPin, clockPin, LSBFIRST, numLed);//le mandamos cuatro datos primero la data despues el pin del reloj , el bit menos significativo
  digitalWrite(lachtPin, HIGH); //Cuando se termina de cargar los datos se suben 
  delay(1000);

  numLedActual = numLed;
  activacionJuego = 1;
}
void finDelJuego(){ 
  /* Esta funcion se ejecuta cuando se terminarion todos los viajes
   *  Aca se mostrara: 
   *    - un mensaje de felicitaciones
   *    - La cantidad de tiempo que le tomo al usuario realizar todos los viajes
   *    - La cantidad de veces que presiono cada dedo
   *    (los ultimos dos no estan implementados en este codigo)
  */
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("  Felicidades!  ");
  lcd.setCursor(0,1);
  lcd.print(" Fin del juego! ");
  delay(2000);
}
