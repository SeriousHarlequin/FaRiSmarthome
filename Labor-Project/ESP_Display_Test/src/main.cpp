#include "display.h"

void createTasks();
void lvglTimer(void *pvParameters);
TaskHandle_t lvglTimer_handle;

void setup() {
  initTFT();
  createTasks();
}

/***********************************************************************************************************************************/
void loop() { // should only contain lvgl handler
  lv_task_handler();
  vTaskDelay(5 / portTICK_PERIOD_MS);
}

void lvglTimer(void *pvParameters){
  for(;;){
    lv_obj_add_state(ui_Checkbox1, LV_STATE_CHECKED);
    delay(1000);
    // lv_checkbox_set_text(ui_Checkbox1, "Hello");
    // lv_label_set_text(ui_Label1, "Hello");
    lv_obj_clear_state(ui_Checkbox1, LV_STATE_CHECKED);
    delay(1000);
    lv_obj_add_state(ui_Checkbox2, LV_STATE_CHECKED);
    delay(1000);
  }
}

void createTasks(){
  xTaskCreate(
      lvglTimer,      // Function name of the task
      "lvgl handler task",   // Name of the task (e.g. for debugging)
      2048,        // Stack size (bytes)
      NULL,        // Parameter to pass
      1,           // Task priority
      &lvglTimer_handle         // Task handle
  );
}