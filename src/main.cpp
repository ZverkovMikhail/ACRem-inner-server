#include <Arduino.h>
#include <Settings/SettingsHandler.h>
#include <WiFi/WiFiService.h>
#include <AdminWebServer/AdminWebServer.h>


const int BUTTON_INPUT = 4;
bool isClick = false;
int count = 0;

 settings_wifi_callback settings_get_callBack = [](WiFiSettings sett){
    Serial.println("main::settings_get_callBack");
     
    Serial.println(String(sett.wifi_mode));  
    Serial.println(sett.wifi_AP_ssid);    
    Serial.println(sett.wifi_AP_pass);    
    Serial.println(sett.wifi_conn_ssid);    
    Serial.println(sett.wifi_conn_pass); 
    
    ACRemWiFi.init(sett);  
    LocalAdminServer.init();
  };
  
   settings_wifi_callback settings_change_callBack = [](WiFiSettings sett){
    Serial.println("main::settings_change_callBack");
    // Serial.println(String(sett.wifi_mode));  
    // Serial.println(sett.wifi_AP_ssid);    
    // Serial.println(sett.wifi_AP_pass);    
    // Serial.println(sett.wifi_conn_ssid);    
    // Serial.println(sett.wifi_conn_pass);    
  };

void setup() {
  pinMode(BUTTON_INPUT, INPUT_PULLUP);
  Serial.begin(115200 , SERIAL_8N1);
  while (!Serial) 
    delay(50);
  Serial.println("setup");
  DisPlay.init();
  DB.init_db();
  Settings.getWiFiSettings(settings_get_callBack);
  Settings.changeWiFiSettingsEvent(settings_change_callBack);
}

void loop() {
}
