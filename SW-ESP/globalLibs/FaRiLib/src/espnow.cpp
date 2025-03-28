#include "espnow.h"


bool EspNow::init(){
  readMacAddress();
  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return false;
  }
  if(!esp_now_register_recv_cb(OnDataRecv) == ESP_OK) return false;
  if(!esp_now_register_send_cb(OnDataSent) == ESP_OK) return false;

  addBroadcastPeer();
  
  return true;
}

void EspNow::readMacAddress(){
  uint8_t baseMac[6];
  esp_err_t ret = esp_read_mac(baseMac, ESP_MAC_WIFI_STA);

  if (ret == ESP_OK) {
    Serial.printf("%02x:%02x:%02x:%02x:%02x:%02x\n",
                  baseMac[0], baseMac[1], baseMac[2],
                  baseMac[3], baseMac[4], baseMac[5]);
    memcpy(macAddress, baseMac, 6);
  } else {
    Serial.println("Failed to read MAC address");
  }
}


void EspNow::OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void EspNow::addBroadcastPeer(){

  uint8_t broadcast[] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};

  // Add broadcast peer
  esp_now_peer_info_t peerInfo = {};
  memcpy(peerInfo.peer_addr, broadcast, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }


}