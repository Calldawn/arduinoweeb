#include <Ethernet.h>
#include <SPI.h>
#include <WebServer.h>
#include <DHT.h>
#include <Streaming.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#define WEBDUINO_FAIL_MESSAGE "What the Hell you just doing!"
LiquidCrystal_I2C lcd(0x27,16,2);
DHT dht(A1, DHT11);
//IP 位址：192.168.1.130
//卡號：30-D1-6B-88-70-A1
//子網遮罩：255,255,255,0
//匝道：192,168,43,1
IPAddress ip(192,168,9,130);
IPAddress subnet(255,255,255,0);
IPAddress gateway(192,168,9,254);
static byte mac[] = {  0x30, 0xD1, 0x6B, 0x88, 0x70, 0xA9 };
WebServer webserver("", 80);

char name[16]="0";
char value[16]="0";
//網頁內容
P(hornhead) = 
"<!doctype html>"
"<html><head><meta charset = utf-8 >"
"<meta http-equiv=\"refresh\" content \"3\">"
"<title>Arduino網站站</title>"
"</head><body>";

P(form) = 
"<form action=\"http://192.168.9.130/sw\" method=\"post\">"
"訊息：<input name=\"msg\" type = \"text\"><br>"
"燈光：<input name = \"light\" type = \"radio\" value=\"on\">開"
"<input name = \"light\" type = \"radio\" value=\"off\" checked>關"
"<br><br>"
"<input type = \"submit\" value=\"送出\">"
"</form>";

P(hornfoot) = 
"</body></html>";
//網頁內容

//宣告命令
void defaultCmd(WebServer &server, WebServer::ConnectionType type, char *, bool){
  server.httpSuccess();
  if(type != WebServer::HEAD){
    server.printP(hornhead);
    server << "<h1>溫溼度計計</h1>";
    server << "<p>溫度度 : " << dht.readTemperature() << "&deg;C</p>";
    server << "<p>濕度度 : " << dht.readHumidity() << "%</p>";
    server.printP(form);
    server.printP(hornfoot); 
  }
}
void postCmd(WebServer &server, WebServer::ConnectionType type, char *, bool){
  server.httpSuccess();
  if(type == WebServer::POST){
    lcd.clear();
    while(server.readPOSTparam(name,16,  value, 16)){
      server << "<p>" << name <<"的值是" << value << "</p>";
      if(strcmp(name,"msg") ==0){
      server << "<br>" << value;
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
    }
  }
}
//命令

void setup() {
  // put your setup code here, to run once:
  Ethernet.begin(mac, ip, gateway, subnet);
  webserver.setDefaultCommand(&defaultCmd);
  webserver.addCommand("sw", &postCmd);
  webserver.begin();
  pinMode(8, OUTPUT);
  Serial.begin(9600);
  dht.begin();
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Arduino Start!");
  delay(2000);
  lcd.clear();
}

void loop() {
  // put your main code here, to run repeatedly:
  webserver.processConnection();
  Serial.println(name);
}