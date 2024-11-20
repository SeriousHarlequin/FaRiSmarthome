#include <WiFi.h>
#include <PubSubClient.h>



void callback(char *topic, byte *payload, unsigned int length);
void connectWiFi(const char *ssid, const char *password);
void connectMQTT(PubSubClient *client, const char *mqtt_broker, const int mqtt_port, const char *mqtt_username="", const char *mqtt_password="");
