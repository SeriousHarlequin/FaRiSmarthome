#include "display.h"
#include "espnowSlave.h"
#include <ESP32Encoder.h>

void createTasks();
void lvglTimer(void *pvParameters);
TaskHandle_t lvglTimer_handle;
void espNow(void *pvParameters);
ESP32Encoder encoder;

SemaphoreHandle_t lvglMutex;

void setup() {
  lvglMutex = xSemaphoreCreateMutex();
  initTFT();
  createTasks();
  encoder.attachHalfQuad(ROTARY_A, ROTARY_B);
  pinMode(ROTARY_BUTTON, INPUT);

}

/*******************************************Superloops*********************************************************************************/

void loop() { // should only contain lvgl handler
  xSemaphoreTake(lvglMutex, portMAX_DELAY);
  lv_task_handler();
  xSemaphoreGive(lvglMutex);
  vTaskDelay(5 / portTICK_PERIOD_MS);
}

void lvglTimer(void *pvParameters){
  delay(1000);
  lv_group_t* group1 = lv_group_create();
  lv_group_add_obj(group1, ui_Button1);
  lv_group_add_obj(group1, ui_Button2);
  lv_group_add_obj(group1, ui_Button3);

  lv_group_t* group2 = lv_group_create();
  lv_group_add_obj(group2, ui_Button4);
  lv_group_add_obj(group2, ui_Button5);

  lv_group_t* currentGroup = group1;

  lv_group_focus_obj(ui_Button1);
  lv_obj_add_style(lv_group_get_focused(currentGroup), &HighlightStyle, 0);
  
  for(;;){
    vTaskDelay(50);    

    xSemaphoreTake(lvglMutex, portMAX_DELAY);
    if(encoder.getCount() > 1){
      encoder.setCount(0);
      focusNext(currentGroup);
    }

    if(encoder.getCount() < -1){
      encoder.setCount(0);
      focusPrev(currentGroup);
    }

    if(digitalRead(ROTARY_BUTTON) == LOW){
      
      if(
        lv_scr_act() == ui_Screen1 
        && lv_group_get_focused(currentGroup) == ui_Button3
      ){
        moveToScreen2(currentGroup, group2);
      }
      else if(
        lv_scr_act() == ui_Screen2
        && lv_group_get_focused(currentGroup) == ui_Button4
      ){
        moveToScreen1(currentGroup, group1);
      } 
      // lv_obj_add_style(lv_group_get_focused(currentGroup), &HighlightStyle, 0);
      else if (lv_group_get_focused(currentGroup) == ui_Button5)
      {
        ESP.restart();
      }
      
      else lv_event_send(lv_group_get_focused(currentGroup), LV_EVENT_CLICKED, NULL);
      vTaskDelay(100);
    }
    xSemaphoreGive(lvglMutex);

  }
}

void espNow(void *pvParameters){
  espnowSlave.init();  
  while(espnowSlave.macMaster[0] == 0) {
    Serial.println("Looking for master");
    espnowSlave.lookForMaster();
    delay(1000);
  }
  vTaskSuspend(NULL);
}
/********************************************Tasks*********************************************************************************/

void createTasks(){
  xTaskCreate(
      lvglTimer,      // Function name of the task
      "lvgl handler task",   // Name of the task 
      4096,        // Stack size (bytes)
      NULL,        // Parameter to pass
      1,           // Task priority
      &lvglTimer_handle         // Task handle
  );

  xTaskCreate(
      espNow,      // Function name of the task
      "ESP Now",   // Name of the task 
      4096,        // Stack size (bytes)
      NULL,        // Parameter to pass
      1,           // Task priority
      NULL         // Task handle
  );
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

}