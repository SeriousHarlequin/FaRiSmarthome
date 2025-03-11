#ifndef MODULES_DEFINITIONS_H
#define MODULES_DEFINITIONS_H

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

#define SWITCH_ADC 4060
#define MOTION_ADC 3900
#define TOLERANZ 80

#define WAIT_ADC 500

#define ETH_MISO_PIN                    12//11
#define ETH_MOSI_PIN                    11//12
#define ETH_SCLK_PIN                    13//10
#define ETH_CS_PIN                      14//9
#define ETH_INT_PIN                     10//13
#define ETH_RST_PIN                     9//14
#define ETH_ADDR                        1

#define TEMP_SENSOR 0

enum TaskState {
    NONE,
    SWITCH,
    MOTION
};

#endif