  #include <WiFi.h>
  #include <AsyncUDP.h>
  #include <ETHClass.h>  // Modified ETHClass for Ethernet support
  #include "utilities.h"

  // Ethernet settings
  byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED}; // MAC address
  const int udpPort = 12345; // UDP port for broadcasting

  static bool eth_connected = false; // Ethernet connection status
  void WiFiEvent(WiFiEvent_t);

  AsyncUDP udp;

  void setup() {
    Serial.begin(9600);
    while (!Serial || millis() < 5000) {
      ; // wait for serial port to connect. Needed for native USB port only
    }

    WiFi.onEvent(WiFiEvent);
    if (!ETH.beginSPI(ETH_MISO_PIN, ETH_MOSI_PIN, ETH_SCLK_PIN, ETH_CS_PIN, ETH_RST_PIN, ETH_INT_PIN)) {
      printf("Ethernet initialization failed!\n");
    }

    // Wait for Ethernet connection
    while (!eth_connected) {
        printf("Waiting for Ethernet connection...\n");
        delay(1000);
    }

    // if (udp.connect(IPAddress(192, 168, 178, 24), 1234)) {
    //   Serial.println("UDP connected");
    // }
  }

  void loop() {
    IPAddress broadcastIP(192, 168, 178, 255);
    udp.broadcastTo("Anyone here?", udpPort);
    Serial.println("Broadcasted message");
    delay(5000);
  }

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