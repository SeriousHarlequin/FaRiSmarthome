#include <Arduino.h>
#include "espnowMaster.h"
#include "udpBroadcast.h"
#include "WebServer.h"
#include "globalVars.h"

void createTasks();
void udpBrodcast(void *pvParameters);
TaskHandle_t udpBroadcast_handle;


void setup() {
    Serial.begin(9600);
    delay(1000);

    ethernetInit();
    espnowMaster.init();
    initWebServer(&server);
    createTasks();

}

void loop() {

}

void udpBrodcast(void *pvParameters) {
    IPAddress broadcastIP(192, 168, 178, 255);
    for(;;){
        udp.broadcastTo("Anyone here?", UDP_PORT);
        Serial.println("Broadcasted message");
        vTaskDelay(10000 / portTICK_PERIOD_MS);
    }
}

void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
    memcpy(&espnowMaster.msgReceived, incomingData, sizeof(espnowMaster.msgReceived));

    espnowMaster.addPeer(mac); //checks for duplicates

    if(strcmp(espnowMaster.msgReceived.message, "Slave looking") == 0){ //check if mac requ
        espnowMaster.msgToSend.master = true;
        strcpy(espnowMaster.msgToSend.message, "Answer from master");
        memcpy(espnowMaster.msgToSend.mac, ETH.macAddress().c_str(), sizeof(espnowMaster.msgToSend.mac));
        esp_now_send(mac, (uint8_t *) &espnowMaster.msgToSend, sizeof(espnowMaster.msgToSend));
        Serial.println("Answered slave");
    }

    if(strncmp(espnowMaster.msgReceived.message, "temp:", 5) == 0){//if temperature is received
        temp = atof(espnowMaster.msgReceived.message + 5);
        newTemp = true;

        
        
    }


}

void createTasks() {
    xTaskCreate(
        udpBrodcast,      // Function name of the task
        "UDP",   // Name of the task (e.g. for debugging)
        2048,        // Stack size (bytes)
        NULL,        // Parameter to pass
        1,           // Task priority
        &udpBroadcast_handle         // Task handle
    );
}