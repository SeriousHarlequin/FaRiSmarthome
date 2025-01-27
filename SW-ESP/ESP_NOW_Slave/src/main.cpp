#include <Arduino.h>
#include "espnow.h"

// Create a struct_message called myData
struct_message myData;

//------------------- SEND -------------------
uint8_t broadcastAddress[] = {0xa0,0x85,0xe3,0xfb,0x63,0x5c};
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

void setup() {
  Serial.begin(9600);

  WiFi.mode(WIFI_STA);
  // WiFi.begin();
  Serial.print("[DEFAULT] ESP32 Board MAC Address: ");
  readMacAddress();

  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_register_recv_cb(esp_now_recv_cb_t(OnDataRecv));

  //------------------- SEND -------------------
  esp_now_register_send_cb(OnDataSent);

  // Register peer
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  
  // Add peer        
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
  //--------------------------------------------
}

void loop() {
  // Set values to send
  strcpy(mySend.a, "THIS IS A ROBBERY");
  mySend.b = random(1,20);
  mySend.c = 1.2;
  mySend.d = false;
  
  // Send message via ESP-NOW
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &mySend, sizeof(mySend));
   
  if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }
  readMacAddress();
  delay(2000);
}
