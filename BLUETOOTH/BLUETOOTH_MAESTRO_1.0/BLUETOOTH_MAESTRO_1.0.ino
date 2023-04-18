/*
 * PRUEBA MODULO BLUETOOTH ""MAESTRO""¡¡¡¡NO SE PROBO NADA!!!
 * 
 * Se podria hacer una prueba inicial donde los touch se simulen con botones
 * 
 */
//Cada sensor esta simulado con pulsadores hasta que encuentre la libreria para los sensores

#define TTP223_1 A0 //Suma 8 para la izquierda o derecha
#define TTP223_2 A1 //Resta 9 para la derecha o izquierda
#define TTP223_3 A2
#define TTP223_4 A3


int dato_1;
int dato_2;
int dato_3;
int dato_4;

void setup() {
  
  Serial.begin(9600);
  
  pinMode(TTP223_1, INPUT);
  pinMode(TTP223_2, INPUT);
  pinMode(TTP223_3, INPUT);
  pinMode(TTP223_4, INPUT);

}

void loop() {
  
  dato_1 = digitalRead(TTP223_1);
  if(dato_1 == HIGH){

    Serial.print('1');
  }else
  {
    Serial.print('0');
  }
  
  dato_2 = digitalRead(TTP223_2);
  if(dato_2 == HIGH){

    Serial.print('2');
  }else
  {
    Serial.print('0');
  }

  dato_3 = digitalRead(TTP223_3);
  if(dato_3 == HIGH){

    Serial.print('3');
  }else
  {
    Serial.print('0');
  }

  dato_4 = digitalRead(TTP223_4);
  if(dato_4 == HIGH){

    Serial.print('4');
  }else
  {
    Serial.print('0');
  }
}
