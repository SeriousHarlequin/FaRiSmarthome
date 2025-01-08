#include <SPIFFS.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>

extern float temperatureC;

void isr();
void initISR();
void initWebServer(AsyncWebServer*);
void ISRHandler();


