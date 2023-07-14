#include <Arduino.h> 
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "Pages.h"
#include "WiFi/WiFiService.h"
#include "Settings/SettingsHandler.h"

// #include "display/Display.h"

String processor(const String& var)
{
  if(var == "IP_ADDR"){
    Serial.println("IP_ADDR");
    Serial.println(Settings.getActualSettings().wifi_mode);
    if(Settings.getActualSettings().wifi_mode == WIFI_AP){
      Serial.println(WiFi.softAPIP().toString());
      return WiFi.softAPIP().toString();
    }else{
      Serial.println(WiFi.localIP().toString());
      return WiFi.localIP().toString();
    }
  } 
  return String();
}

void indexPage(AsyncWebServerRequest *request) {
    Serial.println(request->url().c_str());
    request->send_P(200, "text/html", index_html, processor);
}
void wifiSettingsPage(AsyncWebServerRequest *request) {
    Serial.println(request->url().c_str());
    request->send_P(200, "text/html", wifi_html, processor);
}
void mqttSettingsPage(AsyncWebServerRequest *request) {
    Serial.println(request->url().c_str());
    request->send_P(200, "text/html", mqtt_html, processor);
}

void action(AsyncWebServerRequest *request)
{
  const char* ssid = request->getParam("ssid", true, false)->value().c_str();
  const char* pswd =  request->getParam("pswd", true, false)->value().c_str();
  Serial.println(ssid);
  Serial.println(pswd);
  Serial.println(WiFi.softAPIP().toString().c_str());
  request->redirect("/");
}

void notFoundPage(AsyncWebServerRequest *request) {
    request->send(404, "text/plain", "Not found");
}