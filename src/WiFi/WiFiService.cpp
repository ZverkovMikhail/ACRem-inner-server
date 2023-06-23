#include <Arduino.h>
#include "WiFiService.h"
#include <ESPAsyncWebServer.h>

void WiFiService::init(WiFiSettings settings){
    WiFi.disconnect();
    delay(500);
    WiFi.mode(settings.wifi_mode);

    if(settings.wifi_mode == WIFI_AP){

        WiFi.softAP(settings.wifi_AP_ssid, settings.wifi_AP_pass);
        Serial.print("settings.wifi_AP_ssid");
        Serial.println(settings.wifi_AP_ssid);
        DisPlay.connectionAPScreen(settings.wifi_AP_ssid, settings.wifi_AP_pass, WiFi.softAPIP().toString().c_str());

    }else if (settings.wifi_mode == WIFI_STA){

        WiFi.begin(settings.wifi_conn_ssid, settings.wifi_conn_pass);
        int tryCount = 0;
        while (WiFi.status() != WL_CONNECTED)
        {
            if(tryCount < 16){
                DisPlay.tryConnectionStaScreen(settings.wifi_conn_ssid, ++tryCount);
                delay(1000);
            }else{
                DisPlay.tryConnectionFailed(settings.wifi_conn_ssid);
                WiFiSettings sett;
                sett = sett.getDefault();
                Settings.setWiFiSettings(sett);
                init(sett);
                return;
            }
            
        }
         DisPlay.connectionStaScreen(settings.wifi_conn_ssid, WiFi.localIP().toString().c_str());
    }
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