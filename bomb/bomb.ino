#include "SSD1306Wire.h"

#define BOMB_OUT 25
#define LED_COUNT 26
#define UP_BTN 13
#define DOWN_BTN 32
#define ARM_BTN 33
SSD1306Wire display(0x3c, SDA, SCL, GEOMETRY_128_32);

void(* resetSoftware)(void) = 0;

void setup() {
  Serial.begin(115200);
  pinMode(BOMB_OUT, OUTPUT);
  pinMode(UP_BTN,INPUT_PULLUP);
  pinMode(DOWN_BTN,INPUT_PULLUP);
  pinMode(ARM_BTN,INPUT_PULLUP);
  display.init();
  display.setContrast(255);

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
       display.setTextAlignment(TEXT_ALIGN_LEFT);
        display.setFont(ArialMT_Plain_16);
        display.clear();
        //0.66: 10,20 otros 0,5
        display.drawString(0, 5, String(tiempo));  
        display.display();
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
      display.setTextAlignment(TEXT_ALIGN_LEFT);
        display.setFont(ArialMT_Plain_16);
        display.clear();
        //0.66: 10,20 otros 0,5
        display.drawString(0, 5, String(tiempo));  
        display.display();
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

  static uint8_t envio=tiempo;
  static uint8_t counter = envio;
  static uint32_t timeOld = 0;
  uint32_t timeNew;

  timeNew = millis();
  if ( (timeNew - timeOld ) > 1000 ) {
    timeOld = timeNew;
    if (counter == 0){ 
    resetSoftware();
    }
    else counter = counter - 1;

    display.setFont(ArialMT_Plain_10);
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.clear();
    display.drawString(20, 16, String(counter));
  }

  Serial.println(millis());
  Serial.println("drawing");
 
  display.display();
  Serial.println(millis());

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
