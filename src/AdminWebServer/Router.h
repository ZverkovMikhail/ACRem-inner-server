#include "Arduino.h" 
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "View.h"

void initRoutes(AsyncWebServer &server){
    server.on("/", HTTP_GET, indexPage);
    server.on("/settings/wifi", HTTP_GET, wifiSettingsPage);
    server.on("/settings/mqtt", HTTP_GET, mqttSettingsPage);
    server.on("/action", HTTP_POST, action);
    server.onNotFound(notFoundPage);
}