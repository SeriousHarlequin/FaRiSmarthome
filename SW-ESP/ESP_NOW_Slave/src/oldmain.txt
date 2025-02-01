#include <Arduino.h>
#include "espnow.h"

// Create a struct_message called myData
struct_message myData;

//------------------- SEND -------------------
uint8_t bridgeAddress[] = {0xa0,0x85,0xe3,0xfb,0x63,0x5c};
struct_message mySend;
esp_now_peer_info_t peerInfo;

// callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}
//--------------------------------------------

// callback function that will be executed when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.println("--------------------");
  Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.print("Char: ");
  Serial.println(myData.a);
  Serial.print("Int: ");
  Serial.println(myData.b);
  Serial.print("Float: ");
  Serial.println(myData.c);
  Serial.print("Bool: ");
  Serial.println(myData.d);
  Serial.print("Message: ");
  Serial.println(myData.message);
  Serial.println("--------------------");
  Serial.println();

}

void setup() {
  Serial.begin(9600);
  delay(200);

  Serial.print("[DEFAULT] ESP32 Board MAC Address: ");
  readMacAddress();

  while(!espNowInit()){
    Serial.println("Error initializing ESP-NOW");
    delay(2000);
  }
  
  // Once ESPNow is successfully Init, we will register for recv/sebd CB to
  // get recv packer info
  esp_now_register_recv_cb(esp_now_recv_cb_t(OnDataRecv));
  esp_now_register_send_cb(OnDataSent);

  // Add peer        
  if (espNowAddPeer(bridgeAddress, 0, false) != ESP_OK){
    Serial.print("Failed to add peer: ");
    for (int i = 0; i < 6; i++){
      Serial.print((char)bridgeAddress[i]);
    }
  }
  //--------------------------------------------
}

void loop() {
  // Set values to send
  // strcpy(mySend.a, "THIS IS A ROBBERY");
  // mySend.b = random(1,20);
  // mySend.c = 1.2;
  // mySend.d = false;
  // strcpy(mySend.message, "Hello");
  
  // // Send message via ESP-NOW
  // esp_err_t result = esp_now_send(bridgeAddress, (uint8_t *) &mySend, sizeof(mySend));
   
  // if (result == ESP_OK) {
  //   Serial.println("Sent with success");
  // }
  // else {
  //   Serial.println("Error sending the data");
  // }
  // readMacAddress();
  delay(2000);
}
