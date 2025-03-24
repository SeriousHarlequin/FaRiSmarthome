#include "globalVars.h"

AsyncWebServer server(80);
AsyncUDP udp;
bool eth_connected = false; //needed by library
float temp = 0;
bool newTemp = false;