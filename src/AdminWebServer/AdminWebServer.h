#ifndef AdminWebServer_h
#define AdminWebServer_h
#include "Arduino.h" 
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "Settings/SettingsHandler.h"
#include <ACStatus.h>
typedef std::function<void(ACStatus stat)> local_admin_status_callback;
class AdminWebServer{
    enum MsgType{ERROR='e', INFO='i'};
    public:
        AdminWebServer();
        void init();
        void setActualStatus(ACStatus *stat);
        void sendStatus(ACStatus *stat);
        void sendMessegeForAll(const char* msg, MsgType msgType=INFO);
        void setStatusCallback(local_admin_status_callback callback);
    private:
        local_admin_status_callback _statusCallback;
        AwsEventHandler wsOnEventStatus();
        AwsEventHandler wsOnEventWiFi();
        AwsEventHandler wsOnEventMQTT();
        ACStatus *actualStatus;
        static void sendMessege(AsyncWebSocketClient * client, const char* msg, MsgType msgType=INFO);

};

extern AdminWebServer LocalAdminServer;
#endif