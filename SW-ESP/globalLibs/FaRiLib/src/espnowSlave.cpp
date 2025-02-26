#include "espnowSlave.h"

bool EspNowSlave::lookForMaster() {
    uint8_t broadcast[] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
    //implement message for broadcast
    msgToSend.master = false;
    strcpy(msgToSend.a, ""); 
    msgToSend.b = 0;
    msgToSend.d = 0; 
    strcpy(msgToSend.message, "Slave looking");
    
    
    esp_err_t er = esp_now_send(broadcast, (uint8_t *) &msgToSend, sizeof(msgToSend));
    Serial.println("Error code: " + String(er));
    return true;
}