#include "espnow_recv.h"
#include "espnow_send.h"
#include <WiFi.h>

typedef struct struct_message {
  char a[32];
  int b;
  float c;
  bool d;
  char message[50];
} struct_message;

bool espNowInit();
void readMacAddress();
void requestMACAddress();
