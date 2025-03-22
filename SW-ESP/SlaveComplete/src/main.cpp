#include <Arduino.h>
#include <DallasTemperature.h>
#include "espnowSlave.h"
#include "slave.h"

void createTasks();
void motionTask(void *pvParameters);
TaskHandle_t motionTask_handle;
void switchTask(void *pvParameters);
TaskHandle_t switchTask_handle;
void temperatureTask(void *pvParameters);
TaskHandle_t temperatureTask_handle;

// EspNowSlave espnow;
Led leds;
float ambientTemp = 0;

void setup() {
    Serial.begin(9600);
    delay(2000);
    
    createTasks();
    vTaskSuspend(motionTask_handle);
    vTaskSuspend(switchTask_handle);
    
    espnowSlave.init();  
    while(espnowSlave.macMaster[0] == 0) {
        Serial.println("Looking for master");
        espnowSlave.lookForMaster();
        leds.showErrorNoMaster();
        delay(1000);
    }
    leds.showMasterFound();
        
        
    TaskState activeModule = checkConnectedModule();
    // Serial.printf("active Task: %d\n", activeModule);
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

void temperatureTask(void *pvParameters){
    OneWire oneWire(TEMP_SENSOR);
    DallasTemperature sensors(&oneWire);
    sensors.begin();
    for(;;){
        sensors.requestTemperatures(); 
        ambientTemp = sensors.getTempCByIndex(0);
        // Serial.printf("Temperature: %.2f\n", ambientTemp);
        vTaskDelay(10000 / portTICK_PERIOD_MS);
    }
}


void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {

    if(sizeof(espnowSlave.msgReceived) != len) return;
    memcpy(&espnowSlave.msgReceived, incomingData, sizeof(espnowSlave.msgReceived));
    
    if (!espnowSlave.msgReceived.master) return;

    if(espnowSlave.macMaster[0] == 0){
        //See if it is a master and store its MAC
        memcpy(espnowSlave.macMaster, mac, 6);
        espnowSlave.addMaster(mac);

    }
    Serial.println("Message received");
    if(strcmp(espnowSlave.msgReceived.message, "req:temp") == 0){
        espnowSlave.msgToSend.master = false;

        // Convert ambientTemp to a C-style string
        char tempStr[10];
        dtostrf(ambientTemp, 6, 2, tempStr); // 6 is the minimum width, 2 is the number of decimal places

        // Construct the message
        snprintf(espnowSlave.msgToSend.message, sizeof(espnowSlave.msgToSend.message), "temp:%s", tempStr);
        esp_err_t er = esp_now_send(
            espnowSlave.macMaster, 
            (uint8_t *) &espnowSlave.msgToSend, 
            sizeof(espnowSlave.msgToSend));

        if (er == ESP_OK) {
            Serial.println("Temp Message sent");
        } else {
            Serial.printf("Temp Error sending message: %d\n", er);
        }
        for(int i = 0; i < 6; i++){
            Serial.printf("%02X ", espnowSlave.macMaster[i]);
        } Serial.println();
        for(int i = 0; i < 6; i++){
            Serial.printf("%02X ", mac[i]);
        }
        Serial.println();
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

    xTaskCreate(
        temperatureTask,      // Function name of the task
        "measureTemp",   // Name of the task (e.g. for debugging)
        2048,        // Stack size (bytes)
        NULL,        // Parameter to pass
        1,           // Task priority
        &temperatureTask_handle         // Task handle
    );
}