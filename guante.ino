volatile int derecha = 0;
volatile int izquierda = 0;
volatile int arriba = 0;
volatile int abajo = 0;

void setup(){

pinMode(indice, INPUT);
pinMode(mayor, INPUT);
pinMode(anular, INPUT);
pinMode(menique, INPUT);

}

void loop(){

if(indice == LOW){
	derecha = 1;
	izquierda = 0;
	arriba = 0;
	abajo = 0;
}
if(mayor == LOW){
	derecha = 0;
	izquierda = 1;
	arriba = 0;
	abajo = 0;
}
if(anular == LOW){
	derecha = 0;
	izquierda = 0;
	arriba = 1;
	abajo = 0;
}
if(menique == LOW){
	derecha = 0;
	izquierda = 0;
	arriba = 0;
	abajo = 1;
}
}