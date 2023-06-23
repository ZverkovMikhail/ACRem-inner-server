#include <Arduino.h>
#include <MQTTClient/MQTTClient.h>
WiFiClient espClient;
PubSubClient client(espClient);

void MQTTClient::reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.println("Attempting MQTT connection.");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      sendSysMsg("ACRem connected");
      // Once connected, publish an announcement...
      // client.publish("outTopic", "hello world");
      // ... and resubscribe
      client.subscribe("acrem12345/#");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void MQTTClient::init(const char* mqtt_server_addr){
    beforTime = millis();
    // WiFiClient _espClient;
    // PubSubClient client(_espClient);
    client.setServer(mqtt_server_addr, 1883);
    auto callback = [this](char* topic, byte* message, unsigned int length){
        Serial.print("Message arrived on topic: ");
        Serial.print(topic);
        Serial.print(". Message: ");
        String messageTemp;
  
        for (int i = 0; i < length; i++) {
        // Serial.print((char)message[i]);
          messageTemp += (char)message[i];
        }
        Serial.println(messageTemp);
        if(_statusCallback){
          ACStatus stat;
          stat.setJson(messageTemp);
          Serial.printf("MQTTClient::init::callback = %d \n", stat.mode);
          _statusCallback(stat);
        }
    };
    client.setCallback(callback);

}
void MQTTClient::loop(){
    if( millis() - beforTime >= 500){
        beforTime = millis();
        if (!client.connected()) {
            reconnect();
        }
        client.loop();
    }
}

void MQTTClient::sendStatus(ACStatus stat){
    String status;
    stat.getJsonStr(status);
    client.publish("acrem12345/status", status.c_str());
}
void MQTTClient::sendSysMsg(String msg){
    String buf = "{\"system\":\"";
    buf += msg;
    buf += "\"}";
    client.publish("acrem12345/sys", buf.c_str());
}
void MQTTClient::setStatusCallback(mqtt_status_callback callback){
    _statusCallback = callback;
}

MQTTClient MQTT;
