#include <Arduino.h>
#include "espnow.h"

uint8_t FirstHost[] = {0xd8,0x3b,0xda,0xa4,0x94,0x84};
uint8_t Broadcast[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
struct_message myData;
esp_now_peer_info_t peerInfo; 

//------------------- RECV -------------------
struct_message myRecv;

// callback function that will be executed when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
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
  Serial.println();
}
//--------------------------------------------

//------------------- SEND -------------------
// callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}
//--------------------------------------------

void setup() {
  Serial.begin(9600);
  delay(200);

  Serial.print("[DEFAULT] ESP32 Board MAC Address: ");
  readMacAddress();

  while(!espNowInit()){
    Serial.println("Error initializing ESP-NOW");
    delay(2000);
  }

  // Once ESPNow is successfully Init, we will register for Send/Recv CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);
  esp_now_register_recv_cb(esp_now_recv_cb_t(OnDataRecv));

  // Add peer        
  if (espNowAddPeer(FirstHost, 0, false) != ESP_OK){
    Serial.print("Failed to add peer: ");
    for (int i = 0; i < 6; i++){
      Serial.print((char)FirstHost[i]);
    }
  }

  if (espNowAddPeer(Broadcast, 0, false) != ESP_OK){
    Serial.print("Failed to add peer: ");
    for (int i = 0; i < 6; i++){
      Serial.print((char)FirstHost[i]);
    }
  }
}

void loop() {
  // Set values to send
  strcpy(myData.a, "THIS IS A CHAR");
  myData.b = random(1,20);
  myData.c = 1.2;
  myData.d = false;
  
  // Send message via ESP-NOW
  esp_err_t result = esp_now_send(FirstHost, (uint8_t *) &myData, sizeof(myData));
   
  if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }
  delay(2000);
}
