#include <SPI.h>
#include <TFT_eSPI.h> // Hardware-specific library
#include <lvgl.h>
#include <ui.h>
#include "FaRiLib.h"




TFT_eSPI tft = TFT_eSPI();       // Invoke custom library

void setup() {
  Serial.begin(115200);

  initTFT(&tft);
  lv_init();
  ui_init();

  Serial.println("Setup done");
}

/***********************************************************************************************************************************/
void loop() {


  // ui_Checkbox1->state = LV_STATE_DEFAULT;
  lv_timer_handler(); /* let the GUI do its work */
  delay(100);

}

