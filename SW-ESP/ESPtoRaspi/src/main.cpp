#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include "WebServer.h"
#define TEMP_SENSOR 0

OneWire oneWire(TEMP_SENSOR);
extern float temperatureC;
bool measureTemp = false;

// Pass our oneWire reference to Dallas Temperature sensor 
DallasTemperature sensors(&oneWire);

AsyncWebServer server(80);

void setup() {

  initISR();
  initWebServer(&server);

  sensors.begin();
  temperatureC = -1;
}

void loop() {
  ISRHandler();
  delay(100);
}

void isr(){//0.1ms
  static unsigned int count;

  if(count == 10000){//1s
    count = 0;
    measureTemp = true;
  }

  count++;  
}

 
void ISRHandler(){
  if(measureTemp){//every one second
    measureTemp = false;
    sensors.requestTemperatures(); 
    temperatureC = sensors.getTempCByIndex(0);

  }

}


