#ifndef SettingsHandler_h
#define SettingsHandler_h
#include <Arduino.h>
#include <sqlite3.h>
#include "WiFiSettings.h"
#include "MQTTSettings.h"
#include "DBHandler.h"

typedef std::function<void(WiFiSettings values)> settings_wifi_callback;
typedef std::function<void(MQTTSettings values)> settings_mqtt_callback;
class SettingsHandler
{
private:
    settings_wifi_callback _changeWiFiHandler;
    settings_mqtt_callback _changeMQTTHandler;
    WiFiSettings _actualSettings;
public:
    void setWiFiSettings(WiFiSettings values);
    void getWiFiSettings(settings_wifi_callback callback);
    void changeWiFiSettingsEvent(settings_wifi_callback callback);
    void setMQTTSettings(MQTTSettings values);
    void getMQTTSettings(settings_mqtt_callback callback);
    void changeMQTTSettingsEvent(settings_mqtt_callback callback);
    void recreate();
    WiFiSettings getActualSettings();

};
extern SettingsHandler Settings;

#endif