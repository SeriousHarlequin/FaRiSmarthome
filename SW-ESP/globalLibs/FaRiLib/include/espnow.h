#ifndef ESPNOW_HEADER_GUARD
#define ESPNOW_HEADER_GUARD
#include <WiFi.h>
#include <esp_now.h>
#include <esp_wifi.h>

typedef struct espnow_message {
  char a[32];
  int b;
  float c;
  bool d;
  char message[50];
} espnow_message;

void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len);

class EspNow{
public:
  uint8_t macAddress[6];
  espnow_message msgToSend;
  espnow_message msgReceived;

  bool init();
  void readMacAddress();

  void static OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status);



};

#endif
