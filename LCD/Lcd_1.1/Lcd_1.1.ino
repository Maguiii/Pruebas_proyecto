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
 * "(num de viajes) " 
 * 
 * 
 * "Inicio del juego"
 * 
 * ESTA VERSION
 * 
 * No utiliza interrupciones (la version con interrupcion no funciona)
 *
 * 
 */

#define incremento 5 //Estos pines los puse por el proteus 
#define inicio 4


LiquidCrystal lcd(12, 11, 10, 9, 8, 7);

volatile int numViajes = 0;
volatile int aceptacion = 0;


void cantViajes();

void setup() {
  
  lcd.begin(16, 2);

  /*Mensaje de Bienvenida*/
  //lcd.blink(); Esto esta comentado porque trae problemas cuando en el proteus aparece "Inicio del juego", habria que ver si en el maletin pasa lo mismo o no
  //delay(1000);
  lcd.print ("  Bienvenido a  ");
  lcd.setCursor(0, 1);
  lcd.print ("  Super Guanti  ");
  delay(1000);
  lcd.clear();
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
    lcd.setCursor(0,0);
    lcd.print("Inicio del juego");
  }
  
}


/*Esta funcion sirve para que el usuario elija la cantidad de viajes que desea realizar, 
 * para hacerlo se cuenta con un pulsador(incremento) 
 * el resultado se guarda en la variable global numViajes 
 * 
 * cuando se activa el boton inicio, se termina el incremento y se cambia el estado de la bandera aceptacion 
 */

void cantViajes(){ //Si esto no funciona se puede probar poniendo todo esto en el main (eliminar la funcion cantViajes)
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
