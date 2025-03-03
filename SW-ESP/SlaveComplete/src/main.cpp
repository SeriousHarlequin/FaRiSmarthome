#include <Arduino.h>
#include "espnowSlave.h"
#include "modulesDefinitions.h"
#include "slave.h"

void createTasks();
void motionTask(void *pvParameters);
TaskHandle_t motionTask_handle;
void switchTask(void *pvParameters);
TaskHandle_t switchTask_handle;

EspNowSlave espnow;

void setup() {
    Serial.begin(9600);
    while (!Serial || millis() < 5000) { ; } //wait for serial connection
    
    createTasks();
    espnow.init();  
    
    while(espnow.macMaster[0] == 0) {
        espnow.lookForMaster();
        Serial.println("Looking for master");
        delay(1000);
    }
    
    int active = checkConnectedModule();

    switch (active)
    {
    case SWITCH:
        /* code */
        break;
    
    default:
        break;
    }
}

void loop() {}

void motionTask(void *pvParameters){
    for(;;){
        Serial.println("Task 1");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void switchTask(void *pvParameters){
    for(;;){
        Serial.println("Task 2");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
    memcpy(&espnow.msgReceived, incomingData, sizeof(espnow.msgReceived));

    if (!espnow.msgReceived.master) return;

    if(espnow.macMaster[0] == 0){
        //See if it is a master and store its MAC
        memcpy(espnow.macMaster, mac, 6);
    }
}

void createTasks(){
    xTaskCreate(
        motionTask,      // Function name of the task
        "Motion",   // Name of the task (e.g. for debugging)
        2048,        // Stack size (bytes)
        NULL,        // Parameter to pass
        1,           // Task priority
        &motionTask_handle         // Task handle
    );

    xTaskCreate(
        switchTask,      // Function name of the task
        "Switch",   // Name of the task (e.g. for debugging)
        2048,        // Stack size (bytes)
        NULL,        // Parameter to pass
        1,           // Task priority
        &switchTask_handle         // Task handle
    );
}