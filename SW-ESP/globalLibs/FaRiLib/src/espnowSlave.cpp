#include "espnowSlave.h"

bool EspNowSlave::lookForMaster() {
    uint8_t broadcast[] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
    //implement message for broadcast
    msgToSend.master = false;
    esp_now_send(broadcast, (uint8_t *) &msgToSend, sizeof(msgToSend));
}