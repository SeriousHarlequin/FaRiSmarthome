#include <SPI.h>
#include <TFT_eSPI.h> // Hardware-specific library
#include <lvgl.h>
#include <ui.h>
#include "FaRiLib.h"

TFT_eSPI tft = TFT_eSPI(displayWidth, displayHeight);       // Invoke custom library

void setup() {
  initTFT(&tft);
  // lv_task_handler();
  pinMode(48, OUTPUT);
  digitalWrite(48, HIGH);
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




}

