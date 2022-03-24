#include <Ethernet.h>
#include <SPI.h>
#include <WebServer.h>
#include <DHT.h>
#include <Streaming.h>
#define WEBDUINO_FAIL_MESSAGE "What the Hell you just doing!"


//IP 位址：192.168.1.130
//卡號：30-D1-6B-88-70-A1
//子網遮罩：255,255,255,0
//匝道：192,168,43,1
IPAddress ip(192,168,9,130);
IPAddress subnet(255,255,255,0);
IPAddress gateway(192,168,9,254);
static byte mac[] = {  0x30, 0xD1, 0x6B, 0x88, 0x70, 0xA9 };
WebServer webserver("", 80);

//網頁內容
P(horn) = 
"<!doctype html>"
"<html><head><meta charset = utf-8 >"
"<title>Arduino網站站</title>"
"</head><body>"
"This is my fist webside!<br>我坐在此心已死，想放屁卻漏了屎<br>歲月磨平了稜角<br>模糊了形狀<br>於是我們從形形色色的人<br>變成了色色的人"
"</body></html>"
"<img src=\"https://i.imgur.com/LDsw0w2.jpg\">";
//網頁內容

//宣告命令
void defaultCmd(WebServer &server, WebServer::ConnectionType type, char *, bool){
  server.httpSuccess();
  if(type != WebServer::HEAD){
    server.printP(horn);
  }
}
//命令

void setup() {
  // put your setup code here, to run once:
  Ethernet.begin(mac, ip, gateway, subnet);
  webserver.setDefaultCommand(&defaultCmd);
  webserver.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  webserver.processConnection();
}
