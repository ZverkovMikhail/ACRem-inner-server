#include <Arduino.h>
#include "SettingsHandler.h"
#include "DBHandler.h"


void SettingsHandler::getWiFiSettings(settings_wifi_callback callback){
    Serial.println("SettingsHandler::getWiFiSettings");  
    jsonValsCallback call = [this, callback](const char *jsonVals){        
        WiFiSettings settings; 
        settings.setJson(jsonVals);
        _actualSettings = settings;
        if (settings.wifi_mode < 1){
            Serial.print("settings.wifi_mode = ");
            Serial.println(String(settings.wifi_mode));
            DB.setDefaultSettings("wifi");
        }        
        callback(settings);
    };
    DB.getSettingValues("wifi", &call);
}

void SettingsHandler::setWiFiSettings(WiFiSettings vals){
    settings_wifi_callback call = [this, &vals](WiFiSettings values){   
        String buf;
        vals.getJsonStr(buf);     
        if(vals != values){
            DB.setSettingValues("wifi", buf.c_str());
            _actualSettings = vals;

            if(_changeWiFiHandler){
                _changeWiFiHandler(vals);
            }
        }
    };
    getWiFiSettings(call);
}

void SettingsHandler::changeWiFiSettingsEvent(settings_wifi_callback callback){
    _changeWiFiHandler = callback;
}

void SettingsHandler::recreate(){
  DB.removeDB();
  DB.init_db();
}
WiFiSettings SettingsHandler::getActualSettings(){
    return _actualSettings;
}

SettingsHandler Settings;
