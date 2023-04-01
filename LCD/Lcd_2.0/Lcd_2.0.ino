#include <LiquidCrystal.h>
#include <TimerOne.h>

/*PRUEBA LCD 2.0
 * 
 * Consiste en el texto inicial (aparecera al prender el proyecto),
 * el texto que dara inicio a la configuracion (cuando el usuario elige la cantidad de viajes) y 
 * la cuenta regresiva antes del inicio del juego
 * 
 * Las respuestas esperadas son:
 * 
 * "  Bienvenido a  "
 * "  Super Guanti  "
 * 
 * 
 * "Una creacion de:"
 * "     M.A.L.     "
 * 
 * 
 * "Cant de viajes: "
 * "(num de viajes) " //La idea es que se muestre como se produce el incremento en esta variable (primero esta en 0, despues en 2, despues en 3, etc) 
 * 
 * 
 * "El juego inicia "
 * "     en: 00     " //Aca se deberia mostrar la cuenta regresiva (solo 5 seg)
 * 
 * 
 * "    A JUGAR!    " //Se muestra al terminar la cuenta regresiva
 * 
 * 
*/

#define incremento 5 //Estos pines los puse por el proteus 
#define inicio 4

LiquidCrystal lcd(12, 11, 10, 9, 8, 7);

volatile int numViajes = 0;
volatile int aceptacion = 0;

volatile int flagRegresion = 0;
volatile int aux = 0;

int regresion;

void cantViajes();
void cuentaRegresiva();

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
    /* 
     * Finalizada la configuracion 
     * Inicia el juego con una cuenta regresiva de 5 seg, al llegar al final inicia el juego en si
     *  
     * flagRegresion es una bandera con tres estados 
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
        lcd.print("    A JUGAR!    "); //Aca iria el el juego en si
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
  regresion = 5 - (aux++);
  lcd.setCursor(10,1);
  lcd.print(regresion);

  if(regresion <= 0){
    lcd.clear(); //El clear esta aca para que no se repita y el "A JUGAR!" titile
    flagRegresion = 2;
  }
}
