#include "espnowSlave.h"

EspNowSlave espnowSlave;

bool EspNowSlave::lookForMaster() {
    uint8_t broadcast[] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
    //implement message for broadcast
    msgToSend.master = false;
    msgToSend.b = 0;
    msgToSend.d = 0; 
    strcpy(msgToSend.message, "Slave looking");
    
    
    esp_err_t er = esp_now_send(broadcast, (uint8_t *) &msgToSend, sizeof(msgToSend));
    Serial.println("Error code: " + String(er));
    return true;
}

bool EspNowSlave::addMaster(const uint8_t * mac) {
    std::array<uint8_t, 6> macAddress; //only conversion
    std::copy(mac, mac + 6, macAddress.begin());

    esp_now_peer_info_t peerInfo = {};
    memcpy(peerInfo.peer_addr, macAddress.data(), 6);
    peerInfo.channel = 0;  
    peerInfo.encrypt = false;

    if(esp_now_is_peer_exist(macAddress.data())){
        Serial.println("Peer already exists");
        return false;
    }

    if (esp_now_add_peer(&peerInfo) != ESP_OK) {
        Serial.println("Failed to add peer");
        return false;
    }

    return true;
}