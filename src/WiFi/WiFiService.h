#ifndef WiFiService_h
#define WiFiService_h
#include <Arduino.h>
#include <WiFi.h>
#include <Settings/SettingsHandler.h>
#include <Display/Display.h>

class WiFiService{
private:
    void connect(WiFiSettings settings);
public:
    WiFiService();
    // void begin();    
    void init(WiFiSettings settings);
};

extern WiFiService ACRemWiFi;

#endif