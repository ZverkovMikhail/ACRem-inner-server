
#ifndef MQTTClient_h
#define MQTTClient_h
#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <ACStatus.h>
#include <Settings/SettingsHandler.h>

typedef std::function<void(ACStatus stat)> mqtt_status_callback;
class MQTTClient
{
private:
    mqtt_status_callback _statusCallback;
    unsigned long beforTimeReconnect;
    unsigned long beforTime;
    long lastMsg = 0;
    char msg[50];
    int value = 0;
    bool inited = false;
    MQTTSettings _settings;
    void sendToServer(const char *endPoint, const char *msg);
    void reconnect();
public:
    ACStatus *actualStatus;
    void init(const char* mqtt_server_addr, MQTTSettings settings, ACStatus *actStat);
    void sendStatus(ACStatus *stat);    
    void sendSysMsg(String msg);
    void setStatusCallback(mqtt_status_callback callback);
    void loop();
    void amilive();
    void sendConnected(String name);
};

extern MQTTClient MQTT;

#endif