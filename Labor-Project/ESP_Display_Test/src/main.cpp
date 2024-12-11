#include <SPI.h>
#include <TFT_eSPI.h> // Hardware-specific library
#include <lvgl.h>
#include <ui.h>
#include "FaRiLib.h"

TFT_eSPI tft = TFT_eSPI(displayWidth, displayHeight);       // Invoke custom library

void setup() {
  Serial1.begin(115200);
  Serial2.begin(115200);
  
  initTFT(&tft);
  // lv_task_handler();
  pinMode(48, OUTPUT);
  digitalWrite(48, HIGH);
  Serial.println("Setup done");
}

/***********************************************************************************************************************************/
void loop() {

  lv_obj_add_state(ui_Checkbox1, LV_STATE_CHECKED);
  lv_timer_handler();
  delay(1000);
  lv_timer_handler();
  // lv_checkbox_set_text(ui_Checkbox1, "Hello");
  // lv_label_set_text(ui_Label1, "Hello");
  lv_obj_clear_state(ui_Checkbox1, LV_STATE_CHECKED);
  lv_timer_handler();
  delay(1000);
  lv_obj_add_state(ui_Checkbox2, LV_STATE_CHECKED);
  delay(1000);
  Serial2.println("2");
  Serial1.println("1");
  // Serial0.println("0");  
  Serial.println("Hello");



}

