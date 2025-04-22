#include <Arduino.h>
#include "espnowMaster.h"
#include "globalVars.h"

void setup() {
    Serial.begin(9600);
    delay(1000);

    espnowMaster.init();

}

void loop() {

    espnowMaster.msgToSend.master = false;
    espnowMaster.msgToSend.b = 0;
    espnowMaster.msgToSend.d = 0; 
    strcpy(espnowMaster.msgToSend.message, "23,ON,192.168.103.100,2");
    
    
    if (!espnowMaster.peers.empty() && !espnowMaster.peers[0].empty()) {
        esp_err_t er = esp_now_send( //send message
            espnowMaster.peers[0].data(), 
            (uint8_t *) &espnowMaster.msgToSend, 
            sizeof(espnowMaster.msgToSend)
        );
    } else {
        Serial.println("No valid peer MAC address available.");
    }
    delay(1000); 
    
}


void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
    memcpy(&espnowMaster.msgReceived, incomingData, sizeof(espnowMaster.msgReceived));

    espnowMaster.addPeer(mac); //checks for duplicates

    if(strcmp(espnowMaster.msgReceived.message, "Slave looking") == 0){ //check if mac requ
        espnowMaster.msgToSend.master = true;
        strcpy(espnowMaster.msgToSend.message, "23,ON,192.168.103.100,2");
        esp_now_send(mac, (uint8_t *) &espnowMaster.msgToSend, sizeof(espnowMaster.msgToSend));
        Serial.println("Answered slave");
    }
}
