#include <Arduino.h>

void task1(void *pvParameters);
TaskHandle_t task1_handle;
void task2(void *pvParameters);
TaskHandle_t task2_handle;

void setup() {
    Serial.begin(9600);
    delay(1000);

    xTaskCreate(
        task1,      // Function name of the task
        "Task 1",   // Name of the task (e.g. for debugging)
        2048,        // Stack size (bytes)
        NULL,        // Parameter to pass
        1,           // Task priority
        &task1_handle         // Task handle
    );
    xTaskCreate(
        task2,      // Function name of the task
        "Task 2",   // Name of the task (e.g. for debugging)
        2048,        // Stack size (bytes)
        NULL,        // Parameter to pass
        1,           // Task priority
        &task2_handle         // Task handle
    );
}

void loop() {}

void task1(void *pvParameters){
    for(;;){
        Serial.println("Task 1");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void task2(void *pvParameters){
    for(;;){
        Serial.println("Task 2");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

