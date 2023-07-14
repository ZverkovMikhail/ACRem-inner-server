#include <ArduinoJson.h>

struct MQTTSettings
{
   String user_key;
   String user_password;
   String dev_key;
   bool operator == (const MQTTSettings &other){
         return (user_key == other.user_key && (user_password == other.user_password) && (dev_key == other.dev_key));
   }
   bool operator != (const MQTTSettings &other){
      return (user_key != other.user_key || (user_password != other.user_password) || (dev_key != other.dev_key));
   }

   void getJsonStr(String& buf){
      DynamicJsonDocument doc(1024);
      JsonObject jsonObj = doc.to<JsonObject>();
      jsonObj["mqtt"]["user_key"] = user_key;
      jsonObj["mqtt"]["user_password"] = user_password;
      jsonObj["mqtt"]["dev_key"] = dev_key;
      serializeJson(jsonObj, buf);
   }
     void setJson(String json){
      DynamicJsonDocument doc(1024);
      deserializeJson(doc, json);
      user_key = doc["mqtt"]["user_key"].as<String>();
      user_password = doc["mqtt"]["user_password"].as<String>();
      dev_key = doc["mqtt"]["dev_key"].as<String>();
   }
   String toString(){
      String ret = F("user_key = "); 
      ret += String(user_key);
      ret += F("\n");

      ret += F("user_password = ");
      ret += user_password;
      ret += F("\n");

      ret += F("dev_key = ");
      ret += dev_key;
      ret += F("\n");
      return ret;
   }
};
