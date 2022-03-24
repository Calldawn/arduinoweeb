#include <SPI.h>
#include <Ethernet.h>
//IP 位址：192.168.1.130
//卡號：30-D1-6B-88-70-A1
//子網遮罩：255,255,255,0
//匝道：192,168,43,1
IPAddress ip(192,168,1,130);
IPAddress subnet(255,255,255,0);
IPAddress gateway(192,168,43,1);
byte mac[] = {  0x30, 0xD1, 0x6B, 0x88, 0x70, 0xA9 };
EthernetServer server(80);

void setup() {
  Serial.begin(9600);
  Ethernet.begin(mac, ip, gateway, subnet);
  server.begin();
  pinMode(13,OUTPUT);
}
void loop() {
  EthernetClient client = server.available();
  if (client){
    while(client.connected()) {
      if(client.available()) {
        client.println("HTTP/1.1 200 OK");
        client.println("Content-Type: text/html");
        client.println();
        
        //內容
        client.println("<!doctype html>");
        client.println("<html><head>");
        client.println("<meta charset = utf-8 >");
        client.println("<title>Arduino有夠難用的辣</title>");
        client.println("</head><body>");
        client.println("This is my fist webside!");
        client.println("<br>吉吉可為");
        client.println("</body></html>");
        //內容
        
        break;
      }
    }
    delay(1);
    client.stop();
  }
}
