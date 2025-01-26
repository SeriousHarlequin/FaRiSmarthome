#include <Arduino.h>
#include <esp_now.h>
#include <esp_wifi.h>

int espNowAddPeer(const uint8_t *peerMac, const uint8_t channel, const bool encrypt);