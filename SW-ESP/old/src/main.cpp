#include <Arduino.h>
#include <mqtt.h>

    WiFiClient espClient;
    PubSubClient client(espClient);

    const char *mqtt_broker = "192.168.20.211";
    const int mqtt_port = 1884;

    

void setup() {

    Serial.begin(9600);
    connectWiFi("WEEEEEE!", "103Safeeasy"); 

    client.setServer(mqtt_broker, mqtt_port);
    client.setCallback(callback);  
    connectMQTT(&client, mqtt_broker, mqtt_port);

    client.subscribe("example/topic");
}



void loop() {
    
    //client.publish("example/topic", "Hi, I'm ESP32 ^^");
    client.loop();
    //delay(2000);
}

