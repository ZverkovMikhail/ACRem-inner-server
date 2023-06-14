#include "Arduino.h" 
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "View.h"

void initRoutes(AsyncWebServer &server){
    server.on("/", HTTP_GET, indexPage);
    server.on("/action", HTTP_POST, action);
    server.onNotFound(notFoundPage);
}