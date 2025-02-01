#include <Arduino.h>
#include "espnowSlave.h"


EspNowSlave espnow;
void setup() {
  Serial.begin(9600);
  while(espnow.macMaster[0] == 0) {
    espnow.lookForMaster();
    delay(1000);
  }

}

void loop() {

  delay(2000);
}

void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&espnow.msgReceived, incomingData, sizeof(espnow.msgReceived));

  if(espnow.macMaster[0] == 0){
    //See if it is a master and store its MAC
  }
}