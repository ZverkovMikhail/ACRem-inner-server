#include <WiFiType.h>
#include <ArduinoJson.h>

struct WiFiSettings
{
   WiFiMode_t wifi_mode;
   String wifi_AP_ssid;
   String wifi_AP_pass;
   String wifi_conn_ssid;
   String wifi_conn_pass;
   WiFiSettings getDefault(){
      WiFiSettings sett;
      sett.wifi_mode = WIFI_AP;
      sett.wifi_AP_ssid = "ACRem-access";
      sett.wifi_AP_pass = "acrem-admin";
      sett.wifi_conn_ssid = "";
      sett.wifi_conn_pass = "";
      return sett;
   }
   bool operator == (const WiFiSettings &other){
         return (wifi_mode == other.wifi_mode && 
           (wifi_AP_ssid == other.wifi_AP_ssid) && (wifi_AP_pass == other.wifi_AP_pass) && 
            (wifi_conn_ssid == other.wifi_conn_ssid) && (wifi_conn_pass == other.wifi_conn_pass));
   }
   bool operator != (const WiFiSettings &other){
      return (wifi_mode != other.wifi_mode || 
           (wifi_AP_ssid != other.wifi_AP_ssid) || (wifi_AP_pass != other.wifi_AP_pass) || 
            (wifi_conn_ssid != other.wifi_conn_ssid) || (wifi_conn_pass != other.wifi_conn_pass));
   }

   void getJsonStr(String& buf){
      DynamicJsonDocument doc(1024);
      JsonObject jsonObj = doc.to<JsonObject>();
      jsonObj["wifi"]["mode"] = wifi_mode;
      jsonObj["wifi"]["ap_ssid"] = wifi_AP_ssid;
      jsonObj["wifi"]["ap_pass"] = wifi_AP_pass;
      jsonObj["wifi"]["conn_ssid"] = wifi_conn_ssid;
      jsonObj["wifi"]["conn_pass"] = wifi_conn_pass;
      serializeJson(jsonObj, buf);
   }
     void setJson(String json){
      DynamicJsonDocument doc(1024);
      deserializeJson(doc, json);
      wifi_mode = (WiFiMode_t)doc["wifi"]["mode"];
      wifi_AP_ssid = doc["wifi"]["ap_ssid"].as<String>();
      wifi_AP_pass = doc["wifi"]["ap_pass"].as<String>();
      wifi_conn_ssid = doc["wifi"]["conn_ssid"].as<String>();
      wifi_conn_pass = doc["wifi"]["conn_pass"].as<String>();
   }
   String toString(){
      String ret = F("wifi_mode = "); 
      ret += String(wifi_mode);
      ret += F("\n");

      ret += F("wifi_AP_ssid = ");
      ret += wifi_AP_ssid;
      ret += F("\n");

      ret += F("wifi_AP_pass = ");
      ret += wifi_AP_pass;
      ret += F("\n");

      ret += F("wifi_conn_ssid = ");
      ret += wifi_conn_ssid;
      ret += F("\n");
      
      ret += F("wifi_conn_pass = ");
      ret += wifi_conn_pass;
      ret += F("\n");
      return ret;
   }
};
