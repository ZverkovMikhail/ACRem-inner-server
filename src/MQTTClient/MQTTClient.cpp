#include <Arduino.h>
#include <MQTTClient/MQTTClient.h>
#include <WiFiClientSecure.h>
WiFiClientSecure espClient;
PubSubClient client(espClient);

void MQTTClient::reconnect() {
  // Loop until we're reconnected
    if( millis() - beforTimeReconnect >= 5000){
        beforTimeReconnect = millis();
    Serial.println("Attempting MQTT connection.");
    // Attempt to connect
    if (client.connect(_settings.dev_key.c_str(), _settings.dev_key.c_str(), _settings.user_password.c_str())) {
      client.subscribe((_settings.user_key + F("/") + _settings.dev_key + F("/#")).c_str());
      sendConnected(_settings.dev_key);
      sendStatus(actualStatus);
      
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
    }
    }
}

void MQTTClient::init(const char* mqtt_server_addr, MQTTSettings settings, ACStatus *actStat){
  Serial.println("MQTTClient::init");
    actualStatus = actStat;
    _settings = settings;
    beforTime = millis();
static const char isrg_root_x1[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIFazCCA1OgAwIBAgIRAIIQz7DSQONZRGPgu2OCiwAwDQYJKoZIhvcNAQELBQAw
TzELMAkGA1UEBhMCVVMxKTAnBgNVBAoTIEludGVybmV0IFNlY3VyaXR5IFJlc2Vh
cmNoIEdyb3VwMRUwEwYDVQQDEwxJU1JHIFJvb3QgWDEwHhcNMTUwNjA0MTEwNDM4
WhcNMzUwNjA0MTEwNDM4WjBPMQswCQYDVQQGEwJVUzEpMCcGA1UEChMgSW50ZXJu
ZXQgU2VjdXJpdHkgUmVzZWFyY2ggR3JvdXAxFTATBgNVBAMTDElTUkcgUm9vdCBY
MTCCAiIwDQYJKoZIhvcNAQEBBQADggIPADCCAgoCggIBAK3oJHP0FDfzm54rVygc
h77ct984kIxuPOZXoHj3dcKi/vVqbvYATyjb3miGbESTtrFj/RQSa78f0uoxmyF+
0TM8ukj13Xnfs7j/EvEhmkvBioZxaUpmZmyPfjxwv60pIgbz5MDmgK7iS4+3mX6U
A5/TR5d8mUgjU+g4rk8Kb4Mu0UlXjIB0ttov0DiNewNwIRt18jA8+o+u3dpjq+sW
T8KOEUt+zwvo/7V3LvSye0rgTBIlDHCNAymg4VMk7BPZ7hm/ELNKjD+Jo2FR3qyH
B5T0Y3HsLuJvW5iB4YlcNHlsdu87kGJ55tukmi8mxdAQ4Q7e2RCOFvu396j3x+UC
B5iPNgiV5+I3lg02dZ77DnKxHZu8A/lJBdiB3QW0KtZB6awBdpUKD9jf1b0SHzUv
KBds0pjBqAlkd25HN7rOrFleaJ1/ctaJxQZBKT5ZPt0m9STJEadao0xAH0ahmbWn
OlFuhjuefXKnEgV4We0+UXgVCwOPjdAvBbI+e0ocS3MFEvzG6uBQE3xDk3SzynTn
jh8BCNAw1FtxNrQHusEwMFxIt4I7mKZ9YIqioymCzLq9gwQbooMDQaHWBfEbwrbw
qHyGO0aoSCqI3Haadr8faqU9GY/rOPNk3sgrDQoo//fb4hVC1CLQJ13hef4Y53CI
rU7m2Ys6xt0nUW7/vGT1M0NPAgMBAAGjQjBAMA4GA1UdDwEB/wQEAwIBBjAPBgNV
HRMBAf8EBTADAQH/MB0GA1UdDgQWBBR5tFnme7bl5AFzgAiIyBpY9umbbjANBgkq
hkiG9w0BAQsFAAOCAgEAVR9YqbyyqFDQDLHYGmkgJykIrGF1XIpu+ILlaS/V9lZL
ubhzEFnTIZd+50xx+7LSYK05qAvqFyFWhfFQDlnrzuBZ6brJFe+GnY+EgPbk6ZGQ
3BebYhtF8GaV0nxvwuo77x/Py9auJ/GpsMiu/X1+mvoiBOv/2X/qkSsisRcOj/KK
NFtY2PwByVS5uCbMiogziUwthDyC3+6WVwW6LLv3xLfHTjuCvjHIInNzktHCgKQ5
ORAzI4JMPJ+GslWYHb4phowim57iaztXOoJwTdwJx4nLCgdNbOhdjsnvzqvHu7Ur
TkXWStAmzOVyyghqpZXjFaH3pO3JLF+l+/+sKAIuvtd7u+Nxe5AW0wdeRlN8NwdC
jNPElpzVmbUq4JUagEiuTDkHzsxHpFKVK7q4+63SM1N95R1NbdWhscdCb+ZAJzVc
oyi3B43njTOQ5yOf+1CceWxG1bQVs5ZufpsMljq4Ui0/1lvh+wjChP4kqKOJ2qxq
4RgqsahDYVvTH9w7jXbyLeiNdd8XM2w9U/t7y0Ff/9yi0GE44Za4rF2LN9d11TPA
mRGunUHBcnWEvgJBQl9nJEiU0Zsnvgc/ubhPgXRR4Xq37Z0j4r7g1SgEEzwxA57d
emyPxgcYxn/eR44/KJ4EBs+lVDR3veyJm+kXQ99b21/+jh5Xos1AnX5iItreGCc=
-----END CERTIFICATE-----
)EOF";

    espClient.setCACert(isrg_root_x1);
    client.setServer(mqtt_server_addr, 8883);
    auto callback = [this](char* topic, byte* message, unsigned int length){
        Serial.print("Message arrived on topic: ");
        Serial.print(topic);
        Serial.print(". Message: ");
        String messageTemp;
  
        for (int i = 0; i < length; i++) {
          messageTemp += (char)message[i];
        }
        Serial.println(messageTemp);
        DynamicJsonDocument doc(1024);
        deserializeJson(doc, messageTemp);
        if(doc["type"]=="cmd"){
          if(doc["cmd"]=="imalive"){
            amilive();    
          }
          if(doc["cmd"]=="get_status"){
            sendStatus(actualStatus);
          }
        }else if (doc["type"]=="status"){
            ACStatus stat;
            stat.setJson(doc);
            Serial.print("doc[status] = ");
            Serial.println(doc["status"].as<String>());
            _statusCallback(stat);
          }
    };
    client.setCallback(callback);    
    inited = true;
}

void MQTTClient::loop(){
    if( millis() - beforTime >= 500){
        beforTime = millis();
        if (inited && !client.connected()) {
            reconnect();
        }
        client.loop();
    }
}
void MQTTClient::sendToServer(const char *endPoint, const char *msg){
  client.publish((_settings.user_key + F("/") + _settings.dev_key + F("/") + endPoint).c_str(), msg);
}
void MQTTClient::sendStatus(ACStatus *stat){
    String status;
    stat->getJsonStr(status);
    sendToServer("status", status.c_str());
}
void MQTTClient::amilive(){
    sendToServer("amilive", "true");
}
void MQTTClient::sendConnected(String name){
    sendToServer("connected", "true");
}
void MQTTClient::sendSysMsg(String msg){
    String buf = "{\"system\":\"";
    buf += msg;
    buf += "\"}";
    sendToServer("sys", buf.c_str());
}
void MQTTClient::setStatusCallback(mqtt_status_callback callback){
    _statusCallback = callback;
}

MQTTClient MQTT;
