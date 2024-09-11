#include <mqtt.h>

void callback(char *topic, byte *payload, unsigned int length) {
    Serial.print("Message arrived in topic: ");
    Serial.println(topic);
    Serial.print("Message:");
    for (int i = 0; i < length; i++) {
        Serial.print((char) payload[i]);
    }
    Serial.println();
    Serial.println("-----------------------");
}

void connectWiFi(const char *ssid, const char *password) {
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.println("Connecting to WiFi..");
    }
}

    
void connectMQTT(PubSubClient *client, const char *mqtt_broker, const int mqtt_port, const char *mqtt_username, const char *mqtt_password) {
    while (!client->connected()) {
        String client_id = "esp32-client-";
        client_id += String(WiFi.macAddress());
        Serial.printf("The client %s connects to the MQTT broker\n", client_id.c_str());
        if (client->connect(client_id.c_str(), mqtt_username, mqtt_password)) {
            Serial.println("Public EMQX MQTT broker connected");
        } else {
            Serial.print("failed with state ");
            Serial.print(client->state());
            delay(2000);
        }
    }
    
}