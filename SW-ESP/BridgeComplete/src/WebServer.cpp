#include "WebServer.h"
#include "espnowMaster.h"
#include <ESPmDNS.h> //temp


void initWebServer(AsyncWebServer* server){


  // Define a route to handle fetch requests
  server->on("/fetchTemp", HTTP_GET, [](AsyncWebServerRequest *request){
    // Process the request and send a response

    // sendRequestAndWait();
    request->send(200, "text/plain", "20");
  });

  // Start the server
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");
  server->begin();
}

void sendRequestAndWait(){ //for sending a request and waiting for a response
  espnowMaster.msgToSend.master = true;
  strcpy(espnowMaster.msgToSend.message, "req:temp");

  esp_err_t er = esp_now_send(
                  espnowMaster.peers.front().data(), 
                  (uint8_t *) &espnowMaster.msgToSend, 
                  sizeof(espnowMaster.msgToSend));
}
