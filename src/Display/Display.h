#ifndef Display_h
#define Display_h
#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>
#include "ico.h"
#include <ACStatus.h>

typedef u8g2_uint_t u8g_uint_t;

class Display{
  public:
    enum Line{FIRST=1, SECOND=2, THIRD=3, FOURTH=4};
    Display();
    void init();
    void clear();
    Display* setLine(Line line, String s);
    void print();
    
    void connectionAPScreen(String wifi_AP_ssid, String wifi_AP_pass, String ip);
    void connectionStaScreen(String wifi_ssid, String ip);
    void tryConnectionStaScreen(String wifi_ssid, int count);
    void tryConnectionFailed(String wifi_ssid);
    void output_status(ACStatus status);

  private:
    U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2;
    String  _line1;
    String  _line2;
    String  _line3;
    String  _line4;
    #define SECONDS 10
    uint8_t flip_color = 0;
    uint8_t draw_color = 1;
    void u8g2_prepare(void);
    void u8g2_disc_circle(uint8_t a);
};

extern Display DisPlay;

#endif