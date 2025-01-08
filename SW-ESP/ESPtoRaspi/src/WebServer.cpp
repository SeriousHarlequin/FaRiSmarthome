#include "WebServer.h"
float temperatureC;

void initISR(){
  hw_timer_t *timer = timerBegin(0,80, true);
  timerAttachInterrupt(timer, &isr, true);
  timerAlarmWrite(timer, 100, true); //0.1ms
  timerAlarmEnable(timer);
}

void initWebServer(AsyncWebServer* server){
  WiFi.begin("FaRiSmart", "87654321");
  // Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    // Serial.print(".");
  }
  // Serial.println("");
  // Serial.print("Connected to WiFi network with IP Address: ");
  // Serial.println(WiFi.localIP());

  // Define a route to handle fetch requests
  server->on("/fetchTemp", HTTP_GET, [](AsyncWebServerRequest *request){
    // Process the request and send a response
    request->send(200, "text/plain", String(temperatureC, 2));
  });

  // Start the server
  server->begin();
}
