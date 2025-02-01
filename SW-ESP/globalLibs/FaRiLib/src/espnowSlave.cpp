#include "espnowSlave.h"

bool EspNowSlave::lookForMaster() {
    uint8_t broadcast[] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
    //implement message for broadcast
    esp_now_send(broadcast, (uint8_t *) &mySend, sizeof(mySend));
}