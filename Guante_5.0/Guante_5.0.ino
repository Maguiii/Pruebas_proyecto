

#define puls1 A0
#define puls2 A1
#define puls3 A2
#define puls4 A3
#define puls5 A4


void setup() {
  
  pinMode(puls1, INPUT);
  pinMode(puls2, INPUT);
  pinMode(puls3, INPUT);
  pinMode(puls4, INPUT);
  pinMode(puls5, INPUT);
  
  Serial.begin(57600); // Configura la comunicación serial con el módulo HC-05
}

void loop() {

  if(digitalRead(puls1) == HIGH){

     Serial.write('1');
     delay(50);
  }
  
 
  if(digitalRead(puls2) == HIGH){

     Serial.write('3');
     delay(50);
  }
  
  if(digitalRead(puls3) == HIGH){

     Serial.write('5');
     delay(50);
  }


  if(digitalRead(puls4) == HIGH){

     Serial.write('7');
     delay(50);
  }


}
