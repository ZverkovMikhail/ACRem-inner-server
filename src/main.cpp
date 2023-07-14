#include <Arduino.h>
#include <Settings/SettingsHandler.h>
#include <WiFi/WiFiService.h>
#include <AdminWebServer/AdminWebServer.h>
#include <MQTTClient/MQTTClient.h>

const int BUTTON_INPUT = 4;
bool isClick = false;
ACStatus actualStatus;


mqtt_status_callback status_callback = [](ACStatus stat){
  String jstr;
  stat.getJsonStr(jstr);
  Serial.printf("main::status_callback = %d\n", stat.power);
  Serial.printf("main::status_callback = %d\n", stat.mode);
  Serial.printf("main::status_callback = %d\n", stat.temp);
  Serial.printf("main::status_callback = %d\n", stat.fan);
  Serial.printf("main::status_callback = %d\n", stat.swing_v);
  actualStatus = stat;
  DisPlay.output_status(stat);
  MQTT.sendStatus(&stat);
};
 settings_wifi_callback settings_get_callBack = [](WiFiSettings sett){
    Serial.println("main::settings_get_callBack");
    
    wifiConnected wifiCallback = [sett](){    

        if (sett.wifi_mode == WIFI_STA){      
            MQTT.init("acrem-broker.chescat.pro", &actualStatus);
        }      
        LocalAdminServer.init();
    };
    ACRemWiFi.setConnectedCallback(wifiCallback);
    ACRemWiFi.init(sett);  

    
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
  configTime(8 * 3600, 0, "pool.ntp.org", "time.nist.gov");
  DisPlay.init();
  DB.init_db();
  Settings.getWiFiSettings(settings_get_callBack);
  Settings.changeWiFiSettingsEvent(settings_change_callBack);
      actualStatus.power = on;
      actualStatus.mode = Auto;
      actualStatus.temp = 20;
      actualStatus.fan = Quiet;
      actualStatus.swing_v = Highest;
  MQTT.setStatusCallback(status_callback);
}

void loop() {
  if(digitalRead(BUTTON_INPUT) == LOW){
    if(!isClick){
      ACRemWiFi.setDefaultSettings();
      isClick = true;
      }
   
  }else
  {
    isClick = false;
  }
  MQTT.loop();
  ACRemWiFi.loop();
}
