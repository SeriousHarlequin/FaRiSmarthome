#include <Arduino.h>
#include "espnowSlave.h"

uint8_t broadcast[] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};

EspNowSlave espnow;

void setup() {
  Serial.begin(9600);
  espnow.init();       
  
  while(espnow.macMaster[0] == 0) {
    espnow.lookForMaster();
    Serial.println("Looking for master");
    delay(1000);
  }
}

void loop() {

  delay(2000);
}

void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&espnow.msgReceived, incomingData, sizeof(espnow.msgReceived));

  if (!espnow.msgReceived.master) return;
  
  if(espnow.macMaster[0] == 0){
    //See if it is a master and store its MAC
    memcpy(espnow.macMaster, mac, 6);
  }
}