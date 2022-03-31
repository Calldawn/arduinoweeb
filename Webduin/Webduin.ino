#include <Ethernet.h>
#include <WebServer.h>
#include <SPI.h>
IPAddress ip(192,168,9,130);
IPAddress subnet(255,255,255,0);
IPAddress gateway(192,168,9,254);
static byte mac[] = {  0x30, 0xD1, 0x6B, 0x88, 0x70, 0xA9 };
WebServer webserver("", 80);

//網頁內容
P(horn) = //網頁原始碼全都整理在這
"<!doctype html>"
"<html><head><meta charset = utf-8 >"
"<title>Arduino網站站</title>"
"</head><body>"
"This is my fist webside!<br>Calldawn 22.03.31"
"</body></html>"
//網頁內容

//宣告命令
void defaultCmd(WebServer &server, WebServer::ConnectionType type, char *, bool){
  server.httpSuccess();
  if(type != WebServer::HEAD){
    server.printP(horn);
  }
}
//宣告命令

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
