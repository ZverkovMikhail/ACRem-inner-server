#include <ArduinoJson.h>
#include "SettingsType.h"
struct AbstractSettings
{
virtual SettingsType getType();
virtual AbstractSettings getDefault();
virtual void getJsonStr(String& buf);
virtual void setJson(String json);
virtual String toString();
};
