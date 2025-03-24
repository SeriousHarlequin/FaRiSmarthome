#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>
#include <esp_wifi.h>
#include "globalVars.h"

void readMacAddress();
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len);
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status);
bool addPeer(const uint8_t * mac);

typedef struct espnow_message {
    bool master;
    char message[50];
    u_int8_t mac[6];
    int b;
    bool d;
} espnow_message;

espnow_message msgToSend;
espnow_message msgReceived;

void setup() {
    Serial.begin(9600);
    delay(1000);

    readMacAddress();
    WiFi.mode(WIFI_STA);
    while (esp_now_init() != ESP_OK) {
      Serial.println("Error initializing ESP-NOW");
    }
    if(!esp_now_register_recv_cb(OnDataRecv) == ESP_OK) Serial.println("Error registering recv callback");
    if(!esp_now_register_send_cb(OnDataSent) == ESP_OK) Serial.println("Error registering send callback");
  
    strcpy(msgToSend.message, "Range Test");
}

unsigned long lastTime = 0;
unsigned long travelTime = 0;
void loop() {
    if(esp_now_send(msgToSend.mac, (uint8_t *) &msgToSend, sizeof(msgToSend)) != ESP_OK){
        Serial.println("Error sending message");
    } else {
        lastTime = millis();
    }

    delay(5000);
}


void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
    memcpy(&msgReceived, incomingData, sizeof(msgReceived));

    addPeer(mac); //checks for duplicates

    if(strcmp(msgReceived.message, "Range Test") == 0){
        if (esp_now_send(mac, (uint8_t *)&msgToSend, sizeof(msgToSend)) != ESP_OK) {
            Serial.println("Error sending response");
        } else {
            Serial.println("Response sent successfully");
        }
    }

}

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
    Serial.print("\r\nLast Packet Send Status:\t");
    Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void readMacAddress(){
    uint8_t baseMac[6];
    esp_err_t ret = esp_read_mac(baseMac, ESP_MAC_WIFI_STA);
  
    if (ret == ESP_OK) {
      Serial.printf("%02x:%02x:%02x:%02x:%02x:%02x\n",
                    baseMac[0], baseMac[1], baseMac[2],
                    baseMac[3], baseMac[4], baseMac[5]);
    } else {
      Serial.println("Failed to read MAC address");
    }
  }

bool addPeer(const uint8_t * mac) {
    std::array<uint8_t, 6> macAddress; //only conversion
    std::copy(mac, mac + 6, macAddress.begin());

    esp_now_peer_info_t peerInfo = {};
    memcpy(peerInfo.peer_addr, macAddress.data(), 6);
    peerInfo.channel = 0;  
    peerInfo.encrypt = false;

    if(esp_now_is_peer_exist(macAddress.data())){
        // Serial.println("Peer already exists");
        return false;
    }

    if (esp_now_add_peer(&peerInfo) != ESP_OK) {
        Serial.println("Failed to add peer");
        return false;
    }

    return true;
}