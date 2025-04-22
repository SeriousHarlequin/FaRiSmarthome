#include "udpBroadcast.h"

void WiFiEvent(WiFiEvent_t event) {
    switch (event) {
        case ARDUINO_EVENT_ETH_START:
            printf("Ethernet Started\n");
            ETH.setHostname("esp32-ethernet");
            break;
        case ARDUINO_EVENT_ETH_CONNECTED:
            printf("Ethernet Connected\n");
            break;
        case ARDUINO_EVENT_ETH_GOT_IP:
            printf("Ethernet MAC: %s\n", ETH.macAddress().c_str());
            printf("IP Address: %s\n", ETH.localIP().toString().c_str());
            printf("Link Speed: %d Mbps\n", ETH.linkSpeed());
            printf("Gateway IP: %s\n", ETH.gatewayIP().toString().c_str());
            eth_connected = true;
            break;
        case ARDUINO_EVENT_ETH_DISCONNECTED:
            printf("Ethernet Disconnected\n");
            eth_connected = false;
            break;
        case ARDUINO_EVENT_ETH_STOP:
            printf("Ethernet Stopped\n");
            eth_connected = false;
            break;
        default:
            break;
    }
}

void ethernetInit() {
    WiFi.onEvent(WiFiEvent);
    if (!ETH.beginSPI(ETH_MISO_PIN, ETH_MOSI_PIN, ETH_SCLK_PIN, ETH_CS_PIN, ETH_RST_PIN, ETH_INT_PIN)) {
        printf("Ethernet initialization failed!\n");
    }

    // Wait for Ethernet connection
    while (!eth_connected) {
        printf("Waiting for Ethernet connection...\n");
        delay(1000);
    }
}