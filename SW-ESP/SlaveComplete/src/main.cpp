#include <Arduino.h>
#include "espnowSlave.h"
#include "slave.h"

void createTasks();
void motionTask(void *pvParameters);
TaskHandle_t motionTask_handle;
void switchTask(void *pvParameters);
TaskHandle_t switchTask_handle;

EspNowSlave espnow;
Led leds;

void setup() {
    Serial.begin(9600);
    delay(2000);
    
    createTasks();
    vTaskSuspend(motionTask_handle);
    vTaskSuspend(switchTask_handle);
    
    espnow.init();  
    while(espnow.macMaster[0] == 0) {
        Serial.println("Looking for master");
        espnow.lookForMaster();
        leds.showErrorNoMaster();
        delay(1000);
    }
    leds.showMasterFound();
        
        
    TaskState activeModule = checkConnectedModule();
    Serial.printf("active Task: %d\n", activeModule);
    leds.showModuleConnected();
    switch (activeModule){
        case SWITCH:
            vTaskResume(switchTask_handle);
            break;

        case MOTION:
            vTaskResume(motionTask_handle);
            break;
        
        case NONE:
        default:
            Serial.println("No module connected");
            leds.showErrorNoModule();
            break;
    }


}

void loop() {}

void motionTask(void *pvParameters){
    for(;;){
        Serial.println("Task MOTION");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void switchTask(void *pvParameters){
    for(;;){
        Serial.println("Task SWITCH");
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