#ifndef AdminWebServer_h
#define AdminWebServer_h
#include "Arduino.h" 
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "Settings/SettingsHandler.h"

class AdminWebServer{
    enum MsgType{ERROR='e', INFO='i'};
    public:
        AdminWebServer();
        void init();
        void sendMessegeForAll(const char* msg, MsgType msgType=INFO);
    private:
        AwsEventHandler wsOnEvent();
        static void sendMessege(AsyncWebSocketClient * client, const char* msg, MsgType msgType=INFO);

};

extern AdminWebServer LocalAdminServer;
#endif