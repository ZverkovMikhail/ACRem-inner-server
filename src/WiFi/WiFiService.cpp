#include <Arduino.h>
#include "WiFiService.h"
#include <ESPAsyncWebServer.h>

void WiFiService::init(WiFiSettings settings){
    _settings = settings;
    beforTime = millis();
    WiFi.disconnect();
    delay(500);
    connected = false;
    WiFi.mode(settings.wifi_mode);

    if(settings.wifi_mode == WIFI_AP){

        WiFi.softAP(settings.wifi_AP_ssid, settings.wifi_AP_pass);
        Serial.print("settings.wifi_AP_ssid");
        Serial.println(settings.wifi_AP_ssid);
        DisPlay.connectionAPScreen(settings.wifi_AP_ssid, settings.wifi_AP_pass, WiFi.softAPIP().toString().c_str());
        if( _connectedCallback){                
            _connectedCallback();
        }

    }else if (settings.wifi_mode == WIFI_STA){        
        WiFi.begin(_settings.wifi_conn_ssid.c_str(), _settings.wifi_conn_pass.c_str());
    }
}
void WiFiService::loop(){
        if((_settings.wifi_mode == WIFI_STA) && (WiFi.status() != WL_CONNECTED) && (millis() - beforTime >= 3000)){
            beforTime = millis();
            connected = false;
            if(tryCount < 16){
                    DisPlay.tryConnectionStaScreen(_settings.wifi_conn_ssid, ++tryCount);
            }else{
                    tryCount = 0;
            }
        }
        if (!connected && (WiFi.status() == WL_CONNECTED)){
            Serial.println("WiFiService::loop() connected");
            if( _connectedCallback){                
            _connectedCallback();
            }
            connected = true;            
            DisPlay.connectionStaScreen(_settings.wifi_conn_ssid, WiFi.localIP().toString().c_str());
        }
}
void WiFiService::setConnectedCallback(wifiConnected connectedCallback){
    _connectedCallback = connectedCallback;
}
void WiFiService::setDefaultSettings(){
    WiFiSettings sett;
    sett = sett.getDefault();
    Settings.setWiFiSettings(sett);
    init(sett);
}
String WiFiService::networksFind(){
    String networks;
    byte numSsid = WiFi.scanNetworks();
    DynamicJsonDocument doc(1024);
    JsonObject jsonObj = doc.to<JsonObject>();

    for (int i = 0; i < (int)numSsid; i++){
        jsonObj["available_networks"][String(i)] = WiFi.SSID(i);
    }
    serializeJson(jsonObj, networks);
    return networks;
};


WiFiService ACRemWiFi;