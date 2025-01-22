#include <ESPmDNS.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
  
const char* ssid = "linksys";
const char* password =  "87654321";
  
AsyncWebServer server(80);
  
void setup(){
  Serial.begin(115200);

  WiFi.setHostname("farismart");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
 
  if(!MDNS.begin("esp32")) {
     Serial.println("Error starting mDNS");
     return;
  }
    
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plain", "Hello World");
  });
  
  server.begin();
}
  
void loop(){}