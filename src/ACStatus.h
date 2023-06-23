
#ifndef ACStatus_H
#define ACStatus_H
#include <ArduinoJson.h>

enum Power
{
    off = 'n',
    on  = 'o'
};

enum Mode
{
    Auto = 'a',
    Fun = 'f',
    Dry = 'd',
    Cool = 'c',
    Heat = 'h'
};

enum Fan
{
    Quiet = 'q',
    Medium = 'm',
    Maximum = 'M',
    Auto_fun = 'a'
};
enum Swing_v
{
    Highest = 'H',
    High = 'h',
    Middle = 'm',
    Low = 'l',
    Auto_swing = 'a'
};

struct ACStatus{
    Power power;
    Mode mode;
    int temp;
    Fan fan;
    Swing_v swing_v;
    void getJsonStr(String& buf){
      DynamicJsonDocument doc(1024);
      JsonObject jsonObj = doc.to<JsonObject>();
      jsonObj["status"]["power"] = power;
      jsonObj["status"]["mode"] = mode;
      jsonObj["status"]["temp"] = temp;
      jsonObj["status"]["fan"] = fan;
      jsonObj["status"]["swing_v"] = swing_v;
      serializeJson(jsonObj, buf);
   }
     void setJson(String json){
      DynamicJsonDocument doc(1024);
      Serial.printf("setJson::json = %s\n", json);
      deserializeJson(doc, json);
      power = doc["status"]["power"].as<Power>();
      mode = doc["status"]["mode"].as<Mode>();
      temp = doc["status"]["temp"].as<int>();
      fan = doc["status"]["fan"].as<Fan>();
      swing_v = doc["status"]["swing_v"].as<Swing_v>();
   }
};
#endif