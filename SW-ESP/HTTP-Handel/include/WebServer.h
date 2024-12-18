#include <SPIFFS.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>

extern bool ledstate;

void isr();
void initISR();
void initWebServer(AsyncWebServer*);
void ISRHandler();


