#ifndef WiFiService_h
#define WiFiService_h
#include <Arduino.h>
#include <WiFi.h>
#include <Settings/SettingsHandler.h>
#include <Display/Display.h>

class WiFiService{
private:
public: 
    void init(WiFiSettings settings);
    String networksFind();
};

extern WiFiService ACRemWiFi;

#endif