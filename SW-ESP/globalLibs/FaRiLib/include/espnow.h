#ifndef ESPNOW_HEADER_GUARD
#define ESPNOW_HEADER_GUARD
#include <WiFi.h>
#include <esp_now.h>
#include <esp_wifi.h>

typedef struct espnow_message {
  bool master;
  char message[50];
  u_int8_t mac[6];
  int b;
  bool d;
} espnow_message;

void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len);

class EspNow{
public:
  uint8_t macAddress[6];
  espnow_message msgToSend;
  espnow_message msgReceived;

  bool init();
  void readMacAddress();
  void addBroadcastPeer();

  void static OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status);



};

#endif
