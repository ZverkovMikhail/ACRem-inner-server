#include "Arduino.h" 
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "AdminWebServer.h"
#include "Router.h"

// #include "ACControl/ACHandler.h"
// #define ARDUINOJSON_DECODE_UNICODE = 0;
AsyncWebServer _server(80);
AsyncWebSocket _wsStatus("/v1/control/status");
AsyncWebSocket _wsWiFi("/v1/settings/wifi");
AsyncWebSocket _wsMQTT("/v1/settings/mqtt");

extern AsyncWebSocketClient *wsClient;
AdminWebServer::AdminWebServer(){
}
void AdminWebServer::setActualStatus(ACStatus *stat){
  this->actualStatus = stat;
}
void AdminWebServer::setStatusCallback(local_admin_status_callback callback){
    _statusCallback = callback;
}
AwsEventHandler AdminWebServer::wsOnEventStatus(){
  AwsEventHandler wsSettingsHandler = [this](AsyncWebSocket * server, AsyncWebSocketClient * client, AwsEventType type, void * arg, uint8_t *data, size_t len){
  if(type == WS_EVT_CONNECT){
    //client connected
    Serial.printf("ws[%s][%u] connect\n", server->url(), client->id());

    // DynamicJsonDocument doc(1024);
    // JsonObject jsonObj = doc.to<JsonObject>();
    Serial.printf("ws[%s][%u] connect\n", server->url(), client->id());
    sendStatus(this->actualStatus);

    
  } else if(type == WS_EVT_DISCONNECT){
    //client disconnected
    Serial.printf("ws[%s][%u] disconnect: %u\n", server->url(), client->id());
  } else if(type == WS_EVT_ERROR){
    //error was received from the other end
    Serial.printf("ws[%s][%u] error(%u): %s\n", server->url(), client->id(), *((uint16_t*)arg), (char*)data);
  } else if(type == WS_EVT_DATA){
    //data packet
    AwsFrameInfo * info = (AwsFrameInfo*)arg;
    if(info->final && info->index == 0 && info->len == len){
      //the whole message is in a single frame and we got all of it's data
      Serial.printf("ws[%s][%u] %s-message[%llu]: \n", server->url(), client->id(), (info->opcode == WS_TEXT)?"text":"binary", info->len);
      if(info->opcode == WS_TEXT){
        data[len] = 0;
        DynamicJsonDocument doc(1024);
        deserializeJson(doc, data);
        
        if (doc.containsKey("status"))
        {          
          ACStatus stat;
          String statJson = doc.as<String>();
          Serial.println(statJson);
          stat.setJson(statJson);
          _statusCallback(stat);
          
        }
        if (doc.containsKey("cmd")){
          if(doc["cmd"] == "r")
            ACRemWiFi.init(Settings.getActualSettings());
        }
                
       
      }
  }
}
};
return wsSettingsHandler;
}
AwsEventHandler AdminWebServer::wsOnEventWiFi(){
  AwsEventHandler wsSettingsHandler = [this](AsyncWebSocket * server, AsyncWebSocketClient * client, AwsEventType type, void * arg, uint8_t *data, size_t len){
  if(type == WS_EVT_CONNECT){
    //client connected
    Serial.printf("ws[%s][%u] connect\n", server->url(), client->id());

    // DynamicJsonDocument doc(1024);
    // JsonObject jsonObj = doc.to<JsonObject>();
    Serial.printf("ws[%s][%u] connect\n", server->url(), client->id());

    settings_wifi_callback wifiCallback = [client](WiFiSettings values){
      String buf;
      values.getJsonStr(buf);
      Serial.println("WS_EVT_CONNECT");
      Serial.println(buf);
      _wsWiFi.textAll(buf);
    };
    Settings.getWiFiSettings(wifiCallback);
    
  } else if(type == WS_EVT_DISCONNECT){
    //client disconnected
    Serial.printf("ws[%s][%u] disconnect: %u\n", server->url(), client->id());
  } else if(type == WS_EVT_ERROR){
    //error was received from the other end
    Serial.printf("ws[%s][%u] error(%u): %s\n", server->url(), client->id(), *((uint16_t*)arg), (char*)data);
  } else if(type == WS_EVT_DATA){
    //data packet
    AwsFrameInfo * info = (AwsFrameInfo*)arg;
    if(info->final && info->index == 0 && info->len == len){
      //the whole message is in a single frame and we got all of it's data
      Serial.printf("ws[%s][%u] %s-message[%llu]: \n", server->url(), client->id(), (info->opcode == WS_TEXT)?"text":"binary", info->len);
      if(info->opcode == WS_TEXT){
        data[len] = 0;
        DynamicJsonDocument doc(1024);
        deserializeJson(doc, data);
        
        if (doc.containsKey("wifi"))
        {          
          WiFiSettings sett;
          String settJson = doc.as<String>();
          sett.setJson(settJson);
          Settings.setWiFiSettings(sett);
          _wsWiFi.textAll(settJson);
          sendMessegeForAll("Новые настройки были сохранены! <br> Для вступления настроек в силу, требуется перезапустить сервер!");
          
        }
        if (doc.containsKey("cmd")){
          if(doc["cmd"] == "r")
            ACRemWiFi.init(Settings.getActualSettings());
        }
                
       
      }
  }
}
};
return wsSettingsHandler;
}
AwsEventHandler AdminWebServer::wsOnEventMQTT(){
    AwsEventHandler wsSettingsHandler = [this](AsyncWebSocket * server, AsyncWebSocketClient * client, AwsEventType type, void * arg, uint8_t *data, size_t len){
  if(type == WS_EVT_CONNECT){
    //client connected
    Serial.printf("ws[%s][%u] connect\n", server->url(), client->id());

    // DynamicJsonDocument doc(1024);
    // JsonObject jsonObj = doc.to<JsonObject>();
    Serial.printf("ws[%s][%u] connect\n", server->url(), client->id());

    settings_mqtt_callback mqttCallback = [client](MQTTSettings values){
      String buf;
      values.getJsonStr(buf);
      _wsMQTT.textAll(buf);
    };
    Settings.getMQTTSettings(mqttCallback);
    
  } else if(type == WS_EVT_DISCONNECT){
    //client disconnected
    Serial.printf("ws[%s][%u] disconnect: %u\n", server->url(), client->id());
  } else if(type == WS_EVT_ERROR){
    //error was received from the other end
    Serial.printf("ws[%s][%u] error(%u): %s\n", server->url(), client->id(), *((uint16_t*)arg), (char*)data);
  } else if(type == WS_EVT_DATA){
    //data packet
    AwsFrameInfo * info = (AwsFrameInfo*)arg;
    if(info->final && info->index == 0 && info->len == len){
      //the whole message is in a single frame and we got all of it's data
      Serial.printf("ws[%s][%u] %s-message[%llu]: \n", server->url(), client->id(), (info->opcode == WS_TEXT)?"text":"binary", info->len);
      if(info->opcode == WS_TEXT){
        data[len] = 0;
        DynamicJsonDocument doc(1024);
        deserializeJson(doc, data);
        
        if (doc.containsKey("mqtt")){
          MQTTSettings sett;
          String settJson = doc.as<String>();
          sett.setJson(settJson);
          Settings.setMQTTSettings(sett);
          _wsMQTT.textAll(settJson);
          sendMessegeForAll("Новые настройки были сохранены! <br> Для вступления настроек в силу, требуется перезапустить сервер!");
        }    
        if (doc.containsKey("cmd")){
          if(doc["cmd"] == "r")
            ACRemWiFi.init(Settings.getActualSettings());
        }
                
       
      }
  }
}
};
return wsSettingsHandler;
}
void AdminWebServer::init(){
  Serial.println("AdminWebServer::init");
    initRoutes(_server);
    _wsStatus.onEvent(wsOnEventStatus());
    _wsWiFi.onEvent(wsOnEventWiFi());
    _wsMQTT.onEvent(wsOnEventMQTT());
    _server.addHandler(&_wsStatus);
    _server.addHandler(&_wsWiFi);
    _server.addHandler(&_wsMQTT);
    _server.begin();
    
}
void AdminWebServer::sendStatus(ACStatus *stat){
    String status;
    stat->getJsonStr(status);
    String _msg = F("{\"status\":");
    _msg += status;
    _msg += F("}");
    _wsStatus.textAll(_msg.c_str());
}
void AdminWebServer::sendMessege(AsyncWebSocketClient * client, const char* msg, MsgType msgType){
  client->printf("{\"message\":{\"text\":\"%s\",\"type\":\"%c\"}}", msg, msgType);
}

void AdminWebServer::sendMessegeForAll(const char* msg, MsgType msgType){
  String _msg = F("{\"message\":{\"text\":\"");
  _msg += msg;
  _msg += F("\",\"type\":\"");
  _msg += (char) msgType;
  _msg += F("\"}}");
  _wsWiFi.textAll(_msg);
  _wsMQTT.textAll(_msg);
}

AdminWebServer LocalAdminServer;