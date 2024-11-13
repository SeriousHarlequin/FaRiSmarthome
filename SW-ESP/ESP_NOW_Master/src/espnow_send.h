#include <Arduino.h>
#include <esp_now.h>
#include <esp_wifi.h>

typedef struct struct_message {
  char a[32];
  int b;
  float c;
  bool d;
} struct_message;

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status);

void readMacAddress();