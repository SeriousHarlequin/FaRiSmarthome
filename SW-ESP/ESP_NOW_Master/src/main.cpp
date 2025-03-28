#include <Arduino.h>
#include "espnowMaster.h"

EspNowMaster espnow;
void setup() {
  Serial.begin(9600);
  delay(1000);

  Serial.print("[DEFAULT] ESP32 Board MAC Address: ");
  espnow.readMacAddress();

  while(!espnow.init()){
    Serial.println("Error initializing ESP-NOW");
    delay(2000);
  }
  esp_now_register_recv_cb(OnDataRecv);

}

void loop() {

  delay(2000);
}

void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&espnow.msgReceived, incomingData, sizeof(espnow.msgReceived));

  espnow.addPeer(mac); //checks for duplicates

  Serial.println("HELL YEAH!");

  espnow.msgToSend.master = true;
  strcpy(espnow.msgToSend.message, "Answer from master");
  esp_now_send(mac, (uint8_t *) &espnow.msgToSend, sizeof(espnow.msgToSend));

  //if a broadcast from a slave is received, send mac and verification
}