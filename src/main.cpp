#include <Arduino.h>
#include <Settings/SettingsHandler.h>
#include <WiFi/WiFiService.h>
#include <AdminWebServer/AdminWebServer.h>
#include <MQTTClient/MQTTClient.h>

const int BUTTON_INPUT = 4;
bool isClick = false;

mqtt_status_callback status_callback = [](ACStatus stat){
  String jstr;
  stat.getJsonStr(jstr);
  Serial.printf("main::status_callback = %d\n", stat.power);
  Serial.printf("main::status_callback = %d\n", stat.mode);
  Serial.printf("main::status_callback = %d\n", stat.temp);
  Serial.printf("main::status_callback = %d\n", stat.fan);
  Serial.printf("main::status_callback = %d\n", stat.swing_v);
  DisPlay.output_status(stat);
};
 settings_wifi_callback settings_get_callBack = [](WiFiSettings sett){
    Serial.println("main::settings_get_callBack");
     
    Serial.println(String(sett.wifi_mode));  
    Serial.println(sett.wifi_AP_ssid);    
    Serial.println(sett.wifi_AP_pass);    
    Serial.println(sett.wifi_conn_ssid);    
    Serial.println(sett.wifi_conn_pass); 
    
    ACRemWiFi.init(sett);  
    LocalAdminServer.init();
    MQTT.init("192.168.0.153");
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
  MQTT.setStatusCallback(status_callback);
}

void loop() {
  if(digitalRead(BUTTON_INPUT) == LOW){
    if(!isClick){
      ACStatus stat;
      stat.power = on;
      stat.mode = Auto;
      stat.temp = 10;
      stat.fan = Quiet;
      stat.swing_v = Highest;
      MQTT.sendStatus(stat);
      isClick = true;
      }
   
  }else
  {
    isClick = false;
  }
  MQTT.loop();
}
