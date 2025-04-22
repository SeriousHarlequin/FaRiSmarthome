#include "WebServer.h"
#include "espnowMaster.h"
#include "globalVars.h"
#include <ESPmDNS.h> //temp



void initWebServer(AsyncWebServer* server){


    // Define a route to handle fetch requests
    server->on("/fetchTemp", HTTP_GET, [](AsyncWebServerRequest *request){
        // Process the request and send a response

        Serial.println("Request sent and received");
        sendRequestAndWait();
        request->send(200, "text/plain", String(temp));
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
                    
    int activate = millis();
    while (!newTemp && activate + 3000 > millis()) {
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }

    newTemp = false;
}
