#ifndef WiFiService_h
#define WiFiService_h
#include <Arduino.h>
#include <WiFi.h>
#include <Settings/SettingsHandler.h>
#include <Display/Display.h>

typedef std::function<void()> wifiConnected;
class WiFiService{
private:
    wifiConnected _connectedCallback;
    WiFiSettings _settings;
    unsigned long beforTime;    
    int tryCount = 0;
    bool connected = false;
public: 
    void init(WiFiSettings settings);
    String networksFind();
    void setDefaultSettings();
    void setConnectedCallback(wifiConnected connectedCallback);
    void loop();
};

extern WiFiService ACRemWiFi;

#endif