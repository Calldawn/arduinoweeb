#include <Ethernet.h>
#include <WebServer.h>
#include <Streaming.h>
#include <SPI.h>
#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);
//設置LCD顯示器

DHT dht(A1, DHT11);
//設置溫濕度感測器

IPAddress ip(192,168,1,130);
IPAddress subnet(255,255,255,0);
IPAddress gateway(192,168,1,1);
static byte mac[] = {  0x30, 0xD1, 0x6B, 0x88, 0x70, 0xA9 };
//設定IP位置、子網路遮罩、預設匝道、實體卡號

WebServer webserver("", 80);
//啟用網路伺服器，設定80埠

//編寫網路原始碼
P(hornhead) = 
"<!doctype html>"
"<html><head><meta charset = utf-8 >"
"<meta http-equiv=\"refresh\" content \"3\">"
"<title>Arduino網站站</title>"
"</head><body>";


P(form) = //網路表單
"<form action=\"http://192.168.1.130/sw\" method=\"post\">"
"訊息：<input name=\"msg\" type = \"text\"><br>"
"燈光：<input name = \"light\" type = \"radio\" value=\"on\">開"
"<input name = \"light\" type = \"radio\" value=\"off\" checked>關"
"<br><br>"
"<input type = \"submit\" value=\"送出\">"
"</form>";

P(hornfoot) = 
"</body></html>";

//宣告命令
void defaultCmd(WebServer &server, WebServer::ConnectionType type, char *, bool){
  server.httpSuccess();
  if(type != WebServer::HEAD){
    server.printP(hornhead);
    server.printP(form);
    server.printP(hornfoot); 
  }
}

char name[16];
char value[16];//宣告接收網頁表單的變數

void postCmd(WebServer &server, WebServer::ConnectionType type, char *, bool){
  server.httpSuccess();
  if(type == WebServer::POST){
    lcd.clear();
    server.printP(hornhead);
    server << "<h1>溫濕度計計</h1>";
    server << "<p>溫度度 : " << dht.readTemperature() << "&deg;C</p>";
    server << "<p>濕度度 : " << dht.readHumidity() << "%</p>";
    while(server.readPOSTparam(name,16,  value, 16)){
      if(strcmp(name,"msg") ==0){
      server << "<br>" << "訊息: " << value << "<br><br>且<br>";
      lcd.print(value);
      }
      if(strcmp(name,"light") ==0){
        server << "<p>燈光已經";
        if(strcmp(value,"on") ==0){
          server << "打開</p>";
          digitalWrite(8, HIGH);
          lcd.setCursor(3,1);
          lcd.print("Light ON!");
        } else if (strcmp(value,"off") ==0){
          server << "關閉</p>";
          digitalWrite(8, LOW);
          lcd.setCursor(3,1);
          lcd.print("Light OFF!");
        }
      }
      server.printP(hornfoot);
    }
  }
}

void setup() {
  // put your setup code here, to run once:
  
  Ethernet.begin(mac, ip, gateway, subnet);//啟用網路擴充模組

  webserver.setDefaultCommand(&defaultCmd);
  webserver.addCommand("sw", &postCmd);//設置命令
  webserver.begin();//啟動網路伺服器

  pinMode(8, OUTPUT);
  dht.begin();//啟動溫濕度感測器
  lcd.init();//啟動顯示器
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Arduino Start!");
  delay(2000);
  lcd.clear();
}

void loop() {
  // put your main code here, to run repeatedly:
  webserver.processConnection();//處理用戶需求
}
