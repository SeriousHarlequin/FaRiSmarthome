#include <SPI.h>
#include <TFT_eSPI.h> // Hardware-specific library
#include <lvgl.h>
#include <ui.h>
#include "FaRiLib.h"
#include "FastLED.h"

TFT_eSPI tft = TFT_eSPI(displayWidth, displayHeight);       // Invoke custom library




// For led chips like WS2812, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
// Clock pin only needed for SPI based chipsets when not using hardware SPI
#define NUM_LEDS 6
#define DATA_PIN 42
//define CLOCK_PIN- 

CRGB leds[NUM_LEDS];


void setup() {
  Serial1.begin(115200);
  Serial2.begin(115200);
  
  initTFT(&tft);
  // lv_task_handler();
  pinMode(48, OUTPUT);
  digitalWrite(48, HIGH);
  Serial.println("Setup done");
  FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);  // GRB ordering is typical
}

/***********************************************************************************************************************************/
void loop() {

  lv_obj_add_state(ui_Checkbox1, LV_STATE_CHECKED);
  lv_timer_handler();

    leds[0] = CRGB(255,255,255);
    leds[1] = CRGB(255,255,255);
    leds[2] = CRGB(255,255,255);
    leds[3] = CRGB(255,255,255);
    leds[4] = CRGB(255,255,255);
    leds[5] = CRGB(255,255,255);
    FastLED.show();

  delay(1000);

    leds[0] = CRGB(255,0,0);
    leds[1] = CRGB(0,255,0);
    leds[2] = CRGB(0,255,0);
    leds[3] = CRGB(0,0,255);
    leds[4] = CRGB(0,0,255);
    leds[5] = CRGB(0,0,255);
    FastLED.show();

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
