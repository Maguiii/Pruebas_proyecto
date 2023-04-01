#include <LiquidCrystal.h>

/*PRUEBA LCD 1.0 
 * 
 * Se esta probando el texto inicial (aparecera al prender el proyecto) y 
 * La configuracion de la cantidad de viajes
 * Para terminar con el incremento se utiliza un pulsador de aceptacion (mostrara solo un mensaje y detendra el incremento)
 * 
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
 * "Inicio del juego"
 * 
 * ESTA VERSION -- NO FUNCIONA
 * 
 * Utiliza una interrupcion en el pulsador de inicio 
 *
 * 
 */

#define incremento 5//Hay que declarar en que pines del arduino va esto
#define inicio 4


/*BOTON ---> INICIO
 * 
 * INTERRUPCION ---> INTERRUPCION
 * 
 * VARIABLE ---> ACEPTACION
*/

LiquidCrystal lcd(12, 11, 10, 9, 8, 7);

volatile int aceptacion = 0;
volatile int numViajes = 0;


void cantViajes();

void setup() {
  
  lcd.begin(16, 2);
  lcd.blink();
  delay(1000);//Aca se usa un delay no se si vale la pena sacarlo
  lcd.print ("  Bienvenido a  ");
  lcd.setCursor(0, 1);
  lcd.print ("  Super Guanti  ");
  delay(1000);
  lcd.clear();
  lcd.print ("Una creacion de:");
  lcd.setCursor(0, 1);
  lcd.print ("     M.A.L.     ");
  delay(1000);
  
  pinMode(incremento, INPUT);
  pinMode(inicio, INPUT);
  
  attachInterrupt(digitalPinToInterrupt(inicio), interrupcion, RISING);
}

void loop() {
  /*Al iniciar, se elije la cantidad de viajes que se haran con la grua
  Esto se hace guarda en la variable numViajes a travez de la funcion cantViajes()*/
  if(aceptacion == 0){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Cant de viajes:");
    cantViajes();
  }
  else{
    lcd.setCursor(0,0);
    lcd.print("Inicio del juego");
  }

}


/*Esta funcion sirve para que el usuario elija la cantidad de viajes que desea realizar, 
 * para hacerlo se cuenta con un pulsador(incremento) 
 * el resultado se guarda en la variable global numViajes*/

void cantViajes(){ //Si esto no funciona se puede probar poniendo todo esto en el main (eliminar la funcion cantViajes)
  do{
    if(digitalRead(incremento) == LOW){
      numViajes++; //Esto se podria hacer de 5 en 5
      delay(300); //Este delay hay que sacarlo en un futuro, es para la retencion del pulsador
      lcd.setCursor(0,1);
      lcd.print(numViajes);
    }
  }while(aceptacion == 0);
}

void interrupcion(){
  aceptacion = 1;
  lcd.clear();
}
