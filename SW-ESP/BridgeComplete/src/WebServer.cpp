#include "WebServer.h"
#include <ESPmDNS.h> //temp


void initWebServer(AsyncWebServer* server){


  // Define a route to handle fetch requests
  server->on("/fetchTemp", HTTP_GET, [](AsyncWebServerRequest *request){
    // Process the request and send a response
    request->send(200, "text/plain", "20");
  });

  // Start the server
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");
  server->begin();
}
