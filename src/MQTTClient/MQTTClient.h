
#ifndef MQTTClient_h
#define MQTTClient_h
#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <ACStatus.h>

typedef std::function<void(ACStatus stat)> mqtt_status_callback;
class MQTTClient
{
private:
    mqtt_status_callback _statusCallback;
    unsigned long beforTime;
    long lastMsg = 0;
    char msg[50];
    int value = 0;
    void reconnect();
public:
    void init(const char* mqtt_server_addr);
    void sendStatus(ACStatus stat);    
    void sendSysMsg(String msg);
    void setStatusCallback(mqtt_status_callback callback);
    void loop();
};

extern MQTTClient MQTT;

#endif