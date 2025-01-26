#include "espnow_recv.h"
#include "espnow_send.h"

typedef struct struct_message {
  char a[32];
  int b;
  float c;
  bool d;
} struct_message;

bool espNowInit();
void readMacAddress();
void requestMACAddress();