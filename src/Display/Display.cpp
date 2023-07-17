#include <Arduino.h>
#include "Display.h"

Display::Display() : u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE, /* clock=*/22, /* data=*/21){
}

void Display::init(){
    clear();
    u8g2.begin();
    u8g2_prepare();
    delay(50);
}
void testPrint(String s){
  Serial.println(s);
}
void Display::clear(){
  this->_line1 = "";
  this->_line2 = "";
  this->_line3 = "";
  this->_line4 = "";
}

Display* Display::setLine(Line line, String s){
    switch (line)
    {
    case FIRST:
      /* code */
      this->_line1 = s;
    case SECOND:
      this->_line2 = s;
      break;
    case THIRD:
      this->_line3 = s;
      break;
    case FOURTH:
      this->_line4 = s;
      break;
    
    default:
      break;
    }
    return this;
}

void Display::print(){
    // u8g2.setColorIndex(draw_color);
    // u8g2.setFont(u8g2_font_8x13B_tf);
    u8g2.firstPage();  
    do {
      u8g2.drawStr(0,0, this->_line1.c_str());
      u8g2.drawStr(0,16, this->_line2.c_str());
      u8g2.drawStr(0,32, this->_line3.c_str());
      u8g2.drawStr(0,48, this->_line4.c_str());
    } while( u8g2.nextPage());
}

void Display::connectionAPScreen(String wifi_AP_ssid, String wifi_AP_pass, String ip){
  setLine(DisPlay.FIRST, "WIFI_AP")
    ->setLine(DisPlay.SECOND, wifi_AP_ssid)
    ->setLine(DisPlay.THIRD, wifi_AP_pass)
    ->setLine(DisPlay.FOURTH, ip)
    ->print();
}

void Display::connectionStaScreen(String wifi_ssid, String ip){
  setLine(DisPlay.FIRST, "Connected to")
    ->setLine(DisPlay.SECOND, wifi_ssid)
    ->setLine(DisPlay.THIRD, "ACRem ip:")
    ->setLine(DisPlay.FOURTH, ip)
    ->print();
}

void Display::tryConnectionStaScreen(String wifi_ssid, int count){
    char countStr[] = "               ";
    for (size_t i = 0; i < count; i++)
    {
      countStr[i] = '*';
    }
  
    setLine(DisPlay.FIRST, "Try Connecting")
      ->setLine(DisPlay.SECOND, wifi_ssid)
      ->setLine(DisPlay.THIRD, countStr)
      ->setLine(DisPlay.FOURTH, countStr)
      ->print();
}

void Display::u8g2_prepare(void)
{
      u8g2.setFont(u8g2_font_8x13B_tf);
      u8g2.setFontRefHeightExtendedText();
      u8g2.setDrawColor(1);
      u8g2.setFontPosTop();
      u8g2.setFontDirection(0);
}

void Display::u8g2_disc_circle(uint8_t a)
{
      u8g2.drawStr(0, 0, "drawDisc");
      u8g2.drawDisc(10, 18, 9);
      u8g2.drawDisc(24 + a, 16, 7);
      u8g2.drawStr(0, 30, "drawCircle");
      u8g2.drawCircle(10, 18 + 30, 9);
      u8g2.drawCircle(24 + a, 16 + 30, 7);
}


void Display::output_status(ACStatus status)
{

      u8g2.clearBuffer();
      // u8g2.setBitmapMode(true /* solid */);
      // u8g2.drawXBMP(90, 0, u8g2_logo_heat_width, u8g2_logo_heat_height, logo_dry);

      switch (status.power)
      {
      case off:
            u8g2.drawXBMP(46, 18, u8g2_off_width, u8g2_off_height, logo_off);
            break;
      case on:
            String buf = String(status.temp);
            int len = buf.length() + 1; // Преобразуем строку в массив символов
            char temp[len];
            u8g2.setFont(u8g2_font_fub17_tr);
            u8g2.drawStr(95, 10, "C");
            buf.toCharArray(temp, len);

            // u8g2.setFont(u8g2_font_logisoso42_tn);
            // u8g2.drawStr(35, 12, temp);

            u8g2.setFont(u8g2_font_7Segments_26x42_mn );            
            u8g2.drawStr(32, 15, temp);

            switch (status.mode)
            {
            case Auto:
                  u8g2.drawXBMP(-4, 3, u8g2_logo_auto_width, u8g2_logo_auto_height, logo_auto);
                  break;
            case Fun:
                  u8g2.drawXBMP(-4, 3, u8g2_logo_fun_width, u8g2_logo_fun_height, logo_fun);
                  break;
            case Dry:
                  u8g2.drawXBMP(-4, 3, u8g2_logo_dry_width, u8g2_logo_dry_height, logo_dry);
                  break;
            case Cool:
                  u8g2.drawXBMP(-4, 3, u8g2_logo_cool_width, u8g2_logo_cool_height, logo_cool);
                  break;
            case Heat:
                  u8g2.drawXBMP(-4, 3, u8g2_logo_heat_width, u8g2_logo_heat_height, logo_heat);
                  break;
            }

            switch (status.fan)
            {
            case Quiet:
                  u8g2.drawXBMP(95, 35, u8g2_fun_quiet_width, u8g2_fun_quiet_height, fun_quiet);
                  break;
            case Medium:
                  u8g2.drawXBMP(95, 35, u8g2_fun_medium_width, u8g2_fun_medium_height, fun_medium);
                  break;
            case Maximum:
                  u8g2.drawXBMP(95, 35, u8g2_fun_maximum_width, u8g2_fun_maximum_height, fun_maximum);
                  break;
                  ;
            case Auto_fun:
                  u8g2.drawXBMP(95, 35, u8g2_fun_auto_width, u8g2_fun_auto_height, fun_auto);
                  break;
            }

            if (status.swing_v == Auto_swing)
            {
                  u8g2.drawXBMP(-7, 39, u8g2_swing_ches_width, u8g2_swing_ches_height, swing_ches);
            }
            else
                  u8g2.drawXBMP(-7, 39, u8g2_swing_ches_width, u8g2_swing_ches_height, swing_ches);

            // break;
      }

      u8g2.sendBuffer();
}


  Display DisPlay;