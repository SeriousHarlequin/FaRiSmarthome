#include <Arduino.h>
#include "FastLED.h"

#define NUM_LEDS 4

#define DATA_PIN 2
#define CLOCK_PIN 13

#define SWITCH_PIN 5
#define IR_PIN 4
#define CURRENT_SENSOR_PIN 0
#define MOD_PIN 3
#define BAT_PIN 1

#define NIX 0
#define SWITCH 1
#define MOTION 2
#define SWITCH_ADC 4060
#define MOTION_ADC 3900
#define TOLERANZ 80

#define WAIT_ADC 500
