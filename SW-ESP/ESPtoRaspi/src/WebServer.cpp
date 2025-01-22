#include "WebServer.h"
#include <ESPmDNS.h> //temp
float temperatureC;

void initISR(){
  hw_timer_t *timer = timerBegin(0,80, true);
  timerAttachInterrupt(timer, &isr, true);
  timerAlarmWrite(timer, 100, true); //0.1ms
  timerAlarmEnable(timer);
}

void initWebServer(AsyncWebServer* server){
  // WiFi.setHostname("farismart");
  WiFi.begin("FaRiSmart", "87654321");
  // Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    // Serial.print(".");
  }
  // Serial.println("");
  // Serial.print("Connected to WiFi network with IP Address: ");
  // Serial.println(WiFi.localIP());
  if(!MDNS.begin("farismart")) {
    Serial.println("Error starting mDNS");
    return;
  }

  // Define a route to handle fetch requests
  server->on("/fetchTemp", HTTP_GET, [](AsyncWebServerRequest *request){
    // Process the request and send a response
    request->send(200, "text/plain", String(temperatureC, 2));
  });

  // Start the server
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");
  server->begin();
}
