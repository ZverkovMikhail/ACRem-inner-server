#ifndef SettingsHandler_h
#define SettingsHandler_h
#include <Arduino.h>
#include <sqlite3.h>
#include "WiFiSettings.h"
#include "DBHandler.h"

typedef std::function<void(WiFiSettings values)> settings_wifi_callback;

class SettingsHandler
{
private:
    settings_wifi_callback _changeWiFiHandler;
    WiFiSettings _actualSettings;
public:
    void setWiFiSettings(WiFiSettings values);
    void getWiFiSettings(settings_wifi_callback callback);
    void changeWiFiSettingsEvent(settings_wifi_callback callback);
    void recreate();
    WiFiSettings getActualSettings();

};
extern SettingsHandler Settings;

#endif