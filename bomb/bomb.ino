#include "SSD1306Wire.h"

#define BOMB_OUT 25
#define LED_COUNT 26
#define UP_BTN 13
#define DOWN_BTN 32
#define ARM_BTN 33
SSD1306Wire display(0x3c, SDA, SCL, GEOMETRY_128_32);

void setup() {
  Serial.begin(115200);
  pinMode(25, OUTPUT);
  pinMode(13,INPUT_PULLUP);
  pinMode(32,INPUT_PULLUP);
  pinMode(33,INPUT_PULLUP);

}

void alternarmodos() {
  static int tiempo=20;
  enum class DebounceStates {CONFIG, BOMBA};
  static DebounceStates modoactual =  DebounceStates::CONFIG;
 

  switch (modoactual) {

    case DebounceStates::CONFIG: {

         while(digitalRead(ARM_BTN)==HIGH){
   
    digitalWrite(25, HIGH);
    if (digitalRead(UP_BTN)==LOW)
    {
      tiempo=tiempo+1;
      if (tiempo>=60){
      tiempo=20;}
      delay(200);
      Serial.println("Tiempo:");
      Serial.println(tiempo);
      Serial.print('\n');
          
    }
    
     if (digitalRead(DOWN_BTN)==LOW)
    {
      tiempo=tiempo-1;
      if (tiempo<=10){
      tiempo=20;}
      delay(200);
      Serial.println("Tiempo:");
      Serial.println(tiempo);
      Serial.print('\n');
      
    }
       modoactual = DebounceStates::BOMBA;
         }
         
         break;
      }
    case DebounceStates::BOMBA: {
       

        break;
      }
    

    default:
      Serial.println("Error");
      break;
  }
}


void loop() {
  alternarmodos();
}