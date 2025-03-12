#include "udpBroadcast.h"
#include "WebServer.h"

extern AsyncWebServer server;
extern AsyncUDP udp;
extern bool eth_connected; //needed by library
extern float temp;
extern bool newTemp;