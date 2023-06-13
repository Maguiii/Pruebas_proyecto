#define menique A0
#define anular A1
#define indice A2
#define mayor A3
#define pulgar A4

int estadoPrograma = 0;

void setup() {
  
  pinMode(menique, INPUT);
  pinMode(anular, INPUT);
  pinMode(indice, INPUT);
  pinMode(mayor, INPUT);
  pinMode(pulgar, INPUT);
  
  Serial.begin(57600); // Configura la comunicación serial con el módulo HC-05
}

void loop() {
switch(estadoPrograma){

      case 0:
         
         if(digitalRead(menique) == LOW && digitalRead(mayor) == LOW && digitalRead(indice) == LOW && digitalRead(anular) == LOW  && digitalRead(pulgar) == LOW)
            estadoPrograma = 0;

         if(digitalRead(menique) == HIGH && digitalRead(mayor) == LOW && digitalRead(indice) == LOW && digitalRead(anular) == LOW  && digitalRead(pulgar) == LOW)
            estadoPrograma = 1;
         if(digitalRead(menique) == LOW && digitalRead(mayor) == HIGH && digitalRead(indice) == LOW && digitalRead(anular) == LOW  && digitalRead(pulgar) == LOW)
            estadoPrograma = 2;
         if(digitalRead(menique) == LOW && digitalRead(mayor) == LOW && digitalRead(indice) == HIGH && digitalRead(anular) == LOW  && digitalRead(pulgar) == LOW)
            estadoPrograma = 3;
         if(digitalRead(menique) == LOW && digitalRead(mayor) == LOW && digitalRead(indice) == LOW && digitalRead(anular) == HIGH  && digitalRead(pulgar) == LOW)
            estadoPrograma = 4;
         if(digitalRead(menique) == LOW && digitalRead(mayor) == LOW && digitalRead(indice) == LOW && digitalRead(anular) == LOW  && digitalRead(pulgar) == HIGH)
            estadoPrograma = 5;

      break;
      case 1:
         Serial.write('1');

         if(digitalRead(menique) == LOW && digitalRead(mayor) == LOW && digitalRead(indice) == LOW && digitalRead(anular) == LOW  && digitalRead(pulgar) == LOW)
            estadoPrograma = 0;
      break;
      case 2:
         Serial.write('3');

         if(digitalRead(menique) == LOW && digitalRead(mayor) == LOW && digitalRead(indice) == LOW && digitalRead(anular) == LOW  && digitalRead(pulgar) == LOW)
            estadoPrograma = 0;
      break;
      case 3:
         Serial.write('5');

         if(digitalRead(menique) == LOW && digitalRead(mayor) == LOW && digitalRead(indice) == LOW && digitalRead(anular) == LOW  && digitalRead(pulgar) == LOW)
            estadoPrograma = 0;
      break;
      case 4:
         Serial.write('7');

         if(digitalRead(menique) == LOW && digitalRead(mayor) == LOW && digitalRead(indice) == LOW && digitalRead(anular) == LOW  && digitalRead(pulgar) == LOW)
            estadoPrograma = 0;
      break;
      case 5:
         Serial.write('9');

         if(digitalRead(menique) == LOW && digitalRead(mayor) == LOW && digitalRead(indice) == LOW && digitalRead(anular) == LOW  && digitalRead(pulgar) == LOW)
            estadoPrograma = 0;

      break;
   }
}
