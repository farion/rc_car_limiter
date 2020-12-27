// PWM (Puls Weiten Modulation) alle 20 ms einen Puls senden
int sensorValue = 0; // Sensor Messwert
int nullwert = 1490;
int ausgabewert = 1490;
int zwischenwert;
int x = 4; // speed wert default langsam
int i;
boolean taster;
unsigned long len;
int rw = 0;

#define MOTOR_OUT 9
#define MOTOR_IN 2
#define BTN 8

void setup()
{
  pinMode (MOTOR_OUT, OUTPUT);
  pinMode (LED_BUILTIN, OUTPUT);
  pinMode (BTN, INPUT);
  pinMode (MOTOR_IN, INPUT);
  Serial.begin(9600);
}
void loop()
{

  /*
  //prüfen ob schalter gedrückt wurde
  taster = digitalRead(BTN);
  if (taster == LOW)
  {
    x++; // Speedwert um 1 erhöhen
    switch (x) {
      case 1:
        for (i = 0; i < 1; i++) // 1 mal blinken um Speedwert an zu zeigen
        {
          digitalWrite(LED_BUILTIN, HIGH);
          delay (250);
          digitalWrite(LED_BUILTIN, LOW);
          delay (250);
        }

      break;
      case 4:

        for (i = 0; i < 2; i++) // 2 mal blinken um Speedwert an zu zeigen
        {
          digitalWrite(LED_BUILTIN, HIGH);
          delay (250);
          digitalWrite(LED_BUILTIN, LOW);
          delay (250);
        }
      break;
      case 8:
        for (i = 0; i < 3; i++) // 3 mal blinken um Speedwert an zu zeigen
        {
          digitalWrite(LED_BUILTIN, HIGH);
          delay (250);
          digitalWrite(LED_BUILTIN, LOW);
          delay (250);
        }
      break;
      case 12:
        for (i = 0; i < 4; i++) // 4 mal blinken um Speedwert an zu zeigen
        {
          digitalWrite(LED_BUILTIN, HIGH);
          delay (250);
          digitalWrite(LED_BUILTIN, LOW);
          delay (250);
        }
      break;
      case 13:
        digitalWrite(LED_BUILTIN, HIGH);
        delay (250);
        digitalWrite(LED_BUILTIN, LOW);
        delay (250);
      break;
    }
    
    if (x > 12) {// Speedwert auf 1 setzen wenn 5 erreicht wurde
      x = 1;
    }
  }
*/

  x = 12;


  
  // Lese Messwert vom sender ( kein gas ca 1540, vollgas ca 2050 microsekunden)
  len = pulseIn(MOTOR_IN, HIGH);

  Serial.print("Empfangen: ");
  Serial.println(len);
  
  // Gebe Wert als PWM aus
  zwischenwert = len - nullwert ;

  Serial.print("zwischenwert: ");
  Serial.println(zwischenwert);

  if( x == 1 ){
   ausgabewert = len;  

  } else {
    if (zwischenwert < -50 )
    {
       if(rw == -1){
         Serial.println("Bremsen");
         ausgabewert = nullwert + zwischenwert;  
       }else{
         rw++;
         Serial.println("Rückwärts");
         if(rw > 6){
           ausgabewert = nullwert + (zwischenwert/x);
         } else {
           ausgabewert = nullwert + zwischenwert;  
         }
       }
    }else{
      
      if(zwischenwert > 50){
        rw = -1;
        Serial.println("Vorwärts");
      }else{
        Serial.println("Stehen");
        rw=0;
      }
  
      ausgabewert = nullwert + (zwischenwert/x);  
    }

  }
  

  digitalWrite(MOTOR_OUT, HIGH); // pin9 high setzen
  delayMicroseconds(ausgabewert); // puls in microsekunden warten
  digitalWrite(MOTOR_OUT, LOW); //pin9 low setzen

  Serial.print("Ausgabe: ");
  Serial.println(ausgabewert);
  
  delay(20); // 20 ms warten
}
