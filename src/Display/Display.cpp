#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>
#include "Display.h"


Display::Display() : u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE, /* clock=*/22, /* data=*/21){
}

void Display::init(){
    clear();
    u8g2.begin();
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
    u8g2.setColorIndex(draw_color);
    u8g2.setFont(u8g2_font_8x13B_tf);
    u8g2.firstPage();  
    do {
      u8g2.drawStr(0,14, this->_line1.c_str());
      u8g2.drawStr(0,30, this->_line2.c_str());
      u8g2.drawStr(0,46, this->_line3.c_str());
      u8g2.drawStr(0,60, this->_line4.c_str());
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

void Display::tryConnectionFailed(String wifi_ssid){
    setLine(DisPlay.FIRST, "Connection to")
      ->setLine(DisPlay.SECOND, wifi_ssid)
      ->setLine(DisPlay.THIRD, "")
      ->setLine(DisPlay.FOURTH, "!!! Failed !!!")
      ->print();
    delay(5000);
    setLine(DisPlay.FIRST, "Restarting... ")
      ->setLine(DisPlay.SECOND, "with default")
      ->setLine(DisPlay.THIRD, "network")
      ->setLine(DisPlay.FOURTH, "settings")
      ->print();
    delay(5000);
}


  Display DisPlay;