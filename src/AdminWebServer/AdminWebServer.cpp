#include "Arduino.h" 
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "AdminWebServer.h"
#include "Router.h"

// #include "ACControl/ACHandler.h"
// #define ARDUINOJSON_DECODE_UNICODE = 0;
AsyncWebServer _server(80);
AsyncWebSocket _ws("/wifi_settings");

extern AsyncWebSocketClient *wsClient;
AdminWebServer::AdminWebServer(){
}

AwsEventHandler AdminWebServer::wsOnEvent(){
  AwsEventHandler wsSettingsHandler = [this](AsyncWebSocket * server, AsyncWebSocketClient * client, AwsEventType type, void * arg, uint8_t *data, size_t len){
  if(type == WS_EVT_CONNECT){
    //client connected
    Serial.printf("ws[%s][%u] connect\n", server->url(), client->id());

    // DynamicJsonDocument doc(1024);
    // JsonObject jsonObj = doc.to<JsonObject>();
    Serial.printf("ws[%s][%u] connect\n", server->url(), client->id());

    settings_wifi_callback callback = [client](WiFiSettings values){
      String buf;
      values.getJsonStr(buf);
      Serial.println("WS_EVT_CONNECT");
      Serial.println(buf);
      _ws.textAll(buf);
    };
    Settings.getWiFiSettings(callback);
    
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
          _ws.textAll(settJson);
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
    initRoutes(_server);
    _ws.onEvent(wsOnEvent());
    _server.addHandler(&_ws);
    _server.begin();
    
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
  _ws.textAll(_msg);
}

AdminWebServer LocalAdminServer;