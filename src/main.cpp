#include <Arduino.h>
#include <Settings/SettingsHandler.h>
#include <WiFi/WiFiService.h>
#include <AdminWebServer/AdminWebServer.h>
#include <Settings/SettingsHandler.h>
#include <MQTTClient/MQTTClient.h>

const int BUTTON_INPUT = 4;
bool isClick = false;
ACStatus actualStatus;

local_admin_status_callback admin_status_callback = [](ACStatus stat){
  DisPlay.output_status(stat);
  MQTT.sendStatus(&stat);
  LocalAdminServer.sendStatus(&stat);
  actualStatus = stat;
};

mqtt_status_callback status_callback = [](ACStatus stat){
  String jstr;
  stat.getJsonStr(jstr);
  actualStatus = stat;
  //тут вставить код который будет менять режим работы кондиционера, желательно функция принимающая ACStatus на вход
  DisPlay.output_status(stat);
  //Функция MQTT.sendStatus(&stat) отправляет статус на сервер, 
  //можно использовать в любом месте кода. 
  //Требуется добавить отправку статуса на сервер при изменении с пульта.
  MQTT.sendStatus(&stat);
  LocalAdminServer.sendStatus(&stat);
};
 settings_wifi_callback wifi_settings_get_callBack = [](WiFiSettings wifiSettings){
    Serial.println("main::settings_get_callBack");
    
    wifiConnected wifiConnectedCallback = [wifiSettings](){    
        Serial.println("main wifi Connected");
        settings_mqtt_callback mqtt_settings_get_callBack = [wifiSettings](MQTTSettings settings){   

          MQTT.init("acrem-broker.chescat.pro", wifiSettings, settings, &actualStatus);  

        };

      Settings.getMQTTSettings(mqtt_settings_get_callBack);

      LocalAdminServer.init();
      LocalAdminServer.setStatusCallback(admin_status_callback);
      LocalAdminServer.setActualStatus(&actualStatus);
    };
    ACRemWiFi.setConnectedCallback(wifiConnectedCallback);
    ACRemWiFi.init(wifiSettings);  

    
  };
  
   settings_wifi_callback settings_change_callBack = [](WiFiSettings sett){
    Serial.println("main::settings_change_callBack");
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
  Settings.getWiFiSettings(wifi_settings_get_callBack);
  Settings.changeWiFiSettingsEvent(settings_change_callBack);
      actualStatus.power = off;
      actualStatus.mode = Auto;
      actualStatus.temp = 20;
      actualStatus.fan = Quiet;
      actualStatus.swing_v = Auto_swing;
      
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
