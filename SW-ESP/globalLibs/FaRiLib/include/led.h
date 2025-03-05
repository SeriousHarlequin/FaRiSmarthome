#ifndef LED_HEADER_GUARD
#define LED_HEADER_GUARD

#include "FastLED.h"
#include "modulesDefinitions.h"

class Led {
private:
    CRGB leds[NUM_LEDS];
public:
    Led(/* args */);
    ~Led();
    void showErrorNoModule();
    void showModuleConnected();
    void showMasterFound();
    void showErrorNoMaster();
};



#endif