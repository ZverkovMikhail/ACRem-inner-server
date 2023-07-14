
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
      jsonObj["power"] = power;
      jsonObj["mode"] = mode;
      jsonObj["temp"] = temp;
      jsonObj["fan"] = fan;
      jsonObj["swing_v"] = swing_v;
      serializeJson(jsonObj, buf);
   }
     void setJson(String json){
      DynamicJsonDocument doc(1024);
      deserializeJson(doc, json);
      setJson(doc);
      
   }
   void setJson(DynamicJsonDocument json){
        power = json["status"]["power"].as<Power>();
        mode = json["status"]["mode"].as<Mode>();
        temp = json["status"]["temp"].as<int>();
        fan = json["status"]["fan"].as<Fan>();
        swing_v = json["status"]["swing_v"].as<Swing_v>();
   }
};
#endif