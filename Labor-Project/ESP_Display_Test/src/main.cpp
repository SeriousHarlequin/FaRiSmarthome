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
      vTaskDelay(200);
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
  
  char value1[16], value2[16], value3[16], value4[16];
  sscanf(espnowSlave.msgReceived.message, "%15[^,],%15[^,],%15[^,],%15[^,]", value1, value2, value3, value4);
  
  xSemaphoreTake(lvglMutex, portMAX_DELAY);

  char macStr[18];
  snprintf(macStr, sizeof(macStr), "%02X:%02X:%02X:%02X:%02X:%02X", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
  lv_label_set_text_fmt(ui_MacLabel, "MAC: %s", macStr);
  lv_obj_add_state(ui_MasterFound, LV_STATE_CHECKED);
  lv_obj_set_x(ui_MacLabel, lv_obj_get_x(ui_MacLabel) + 15);

  lv_label_set_text_fmt(ui_tempLabel, "Temperature[°C]: %s", value1);
  lv_label_set_text_fmt(ui_switchLabel, "Switch State: %s", value2);
  lv_obj_set_x(ui_switchLabel, lv_obj_get_x(ui_switchLabel) - 25);

  lv_label_set_text_fmt(ui_IPLabel, "IP: %s", value3);

  //show active nodes
  if (strcmp(value4, "1") == 0) {
    lv_obj_add_state(ui_Checkbox1, LV_STATE_CHECKED);
  } else if (strcmp(value4, "2") == 0) {
    lv_obj_add_state(ui_Checkbox1, LV_STATE_CHECKED);
    lv_obj_add_state(ui_Checkbox2, LV_STATE_CHECKED);
  } else if (strcmp(value4, "3") == 0) {
    lv_obj_add_state(ui_Checkbox1, LV_STATE_CHECKED);
    lv_obj_add_state(ui_Checkbox2, LV_STATE_CHECKED);
    lv_obj_add_state(ui_Checkbox3, LV_STATE_CHECKED);
  }

  xSemaphoreGive(lvglMutex);
    Serial.println("Message received");


}