#include <Arduino.h>
#include "WebServer.h"

AsyncWebServer server(80);

void setup() {
  Serial.begin(115200);
  initISR();
  initWebServer(&server);

}

void loop() {
  ISRHandler();
}

void isr(){//0.1ms
  static unsigned int count;

  count++;  
}

 
void ISRHandler(){

}


