#include <Arduino.h>
#include "espnowMaster.h"
#include "udpBroadcast.h"
#include "WebServer.h"

void createTasks();
void udpBrodcast(void *pvParameters);
TaskHandle_t udpBroadcast_handle;

EspNowMaster espnow;
AsyncWebServer server(80);
AsyncUDP udp;
bool eth_connected = false; //needed by library

void setup() {
    Serial.begin(9600);
    delay(1000);

    espnow.init();
    ethernetInit();
    initWebServer(&server);
    createTasks();

}

void loop() {}

void udpBrodcast(void *pvParameters) {
    IPAddress broadcastIP(192, 168, 178, 255);
    for(;;){
        udp.broadcastTo("Anyone here?", UDP_PORT);
        Serial.println("Broadcasted message");
        vTaskDelay(10000 / portTICK_PERIOD_MS);
    }
}

void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
    memcpy(&espnow.msgReceived, incomingData, sizeof(espnow.msgReceived));

    espnow.addPeer(mac); //checks for duplicates

    Serial.println("HELL YEAH!");

    espnow.msgToSend.master = true;
    strcpy(espnow.msgToSend.message, "Answer from master");
    esp_now_send(mac, (uint8_t *) &espnow.msgToSend, sizeof(espnow.msgToSend));

    //if a broadcast from a slave is received, send mac and verification
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