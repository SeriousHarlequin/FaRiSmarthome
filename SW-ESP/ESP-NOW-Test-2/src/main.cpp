#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>
#include <esp_wifi.h>
#include <array>  // needed for std::array
#include "globalVars.h"

void readMacAddress();
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len);
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status);
bool addPeer(const uint8_t * mac);
void wifiSnifferPacketHandler(void *buf, wifi_promiscuous_pkt_type_t type);

typedef struct espnow_message {
    bool master;
    char message[50];
    uint8_t mac[6];
    int b;
    bool d;
} espnow_message;

espnow_message msgToSend;
espnow_message msgReceived;

// Peer MAC address (adjust if needed)
uint8_t peerMac[6] = {0x08, 0x3a, 0xf2, 0xac, 0xc0, 0x64};

unsigned long lastTime = 0;
unsigned long travelTime = 0;
int latestRSSI = 0;  // Global variable to store the latest measured RSSI

void setup() {
    Serial.begin(9600);
    delay(1000);

    readMacAddress();
    WiFi.mode(WIFI_STA);

    // Initialize ESP-NOW
    while (esp_now_init() != ESP_OK) {
        Serial.println("Error initializing ESP-NOW");
        delay(1000);
    }
    if (esp_now_register_recv_cb(OnDataRecv) != ESP_OK)
        Serial.println("Error registering receive callback");
    if (esp_now_register_send_cb(OnDataSent) != ESP_OK)
        Serial.println("Error registering send callback");

    strcpy(msgToSend.message, "Range Test");
    addPeer(peerMac);

    // Enable promiscuous mode to capture all packets (including ESP-NOW)
    esp_wifi_set_promiscuous(true);
    esp_wifi_set_promiscuous_rx_cb(wifiSnifferPacketHandler);
}

void loop() {
    if (esp_now_send(peerMac, (uint8_t *)&msgToSend, sizeof(msgToSend)) != ESP_OK) {
        Serial.println("Error sending message");
    } else {
        lastTime = millis();
    }
    delay(1000);
}

// ESP-NOW receive callback
int avgCounter = 0;
long avgSum = 0;
unsigned int TravelSum = 0;
unsigned int avgTravelTime = 0;
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
    memcpy(&msgReceived, incomingData, sizeof(msgReceived));
    addPeer(mac); // Check for duplicates

    if (strcmp(msgReceived.message, "Range Test") == 0) {
        travelTime = millis() - lastTime;
        avgTravelTime += travelTime; // Accumulate travel times
        avgSum += latestRSSI;        // Accumulate RSSI values
        avgCounter++;                // Increment the counter

        if (avgCounter == 10) { // Calculate averages after 10 samples
            Serial.printf("Average RSSI: %d dBm\n", avgSum / avgCounter);
            Serial.printf("Average Travel Time: %lu ms\n", avgTravelTime / avgCounter);
            // Reset counters and accumulators
            avgCounter = 0;
            avgSum = 0;
            avgTravelTime = 0;
        }
    }            Serial.println(latestRSSI);

}

// ESP-NOW send callback
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
    // Serial.print("\r\nLast Packet Send Status:\t");
    // Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

// Function to read and print the device's MAC address
void readMacAddress() {
    uint8_t baseMac[6];
    esp_err_t ret = esp_read_mac(baseMac, ESP_MAC_WIFI_STA);

    if (ret == ESP_OK) {
        Serial.printf("Device MAC: %02x:%02x:%02x:%02x:%02x:%02x\n",
                      baseMac[0], baseMac[1], baseMac[2],
                      baseMac[3], baseMac[4], baseMac[5]);
    } else {
        Serial.println("Failed to read MAC address");
    }
}

// Function to add a peer if not already added
bool addPeer(const uint8_t * mac) {
    std::array<uint8_t, 6> macAddress;
    std::copy(mac, mac + 6, macAddress.begin());

    esp_now_peer_info_t peerInfo = {};
    memcpy(peerInfo.peer_addr, macAddress.data(), 6);
    peerInfo.channel = 0;
    peerInfo.encrypt = false;

    if (esp_now_is_peer_exist(macAddress.data())) {
        // Peer already exists
        return false;
    }
    if (esp_now_add_peer(&peerInfo) != ESP_OK) {
        Serial.println("Failed to add peer");
        return false;
    }
    return true;
}

// Promiscuous mode callback to capture RSSI from incoming packets
void wifiSnifferPacketHandler(void *buf, wifi_promiscuous_pkt_type_t type) {
    // Cast to a packet structure that contains RX control info.
    wifi_promiscuous_pkt_t *pkt = (wifi_promiscuous_pkt_t *)buf;
    // Update the global RSSI variable with the received signal strength.
    latestRSSI = pkt->rx_ctrl.rssi;

    // If needed, you can add filtering here (e.g., check the source MAC)
    // to only update RSSI for specific ESP-NOW messages.
    //
    // Example (requires additional parsing of the 802.11 header):
    // if (matchesExpectedMAC(pkt)) { ... }
}


/*
m   dbm ms
10m -65 4
20m -80 5
30m -77 4
40m -88 5
60m -90 6
80m -83 6
100m -89 4
160m -89 4ms 

-----indoors-----
m   dbm ms
4 -74 11
8 -84 22
12 -89 21
Stahlbeton

-----through walls-----
m wall dbm ms
2 33cm -68 7

*/