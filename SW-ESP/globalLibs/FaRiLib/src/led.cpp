#include "led.h"

Led::Led(/* args */) {
    FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);  // GRB 

    leds[0] = CRGB(0,0,0);
    leds[1] = CRGB(0,0,0);
    leds[2] = CRGB(0,0,0);
    leds[3] = CRGB(0,0,0);
    // FastLED.show(); //causes kernel panic here, only god knows why
}

Led::~Led()
{
}

void Led::showErrorNoModule(){
    leds[1] = CRGB(40,0,0);
    FastLED.show();
}

void Led::showModuleConnected(){
    leds[1] = CRGB(0,40,0);
    FastLED.show();
}

void Led::showMasterFound(){
    leds[0] = CRGB(0,40,0);
    FastLED.show();
}

void Led::showErrorNoMaster(){
    leds[0] = CRGB(40,0,0);
    FastLED.show();
}

