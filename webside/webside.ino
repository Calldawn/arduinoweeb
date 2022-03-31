#include <SPI.h>
#include <Ethernet.h>
IPAddress ip(192,168,1,130);
IPAddress subnet(255,255,255,0);
IPAddress gateway(192,168,43,1);
byte mac[] = {  0x30, 0xD1, 0x6B, 0x88, 0x70, 0xA9 };
EthernetServer server(80);

void setup() {
  Ethernet.begin(mac, ip, gateway, subnet);
  server.begin();
}
void loop() {
  EthernetClient client = server.available();
  if (client){
    while(client.connected()) {
      if(client.available()) {
        //要一直重複打client.println()，很麻煩
        client.println("HTTP/1.1 200 OK");
        client.println("Content-Type: text/html");
        client.println();
        
        //內容
        client.println("<!doctype html>");
        client.println("<html><head>");
        client.println("<meta charset = utf-8 >");
        client.println("<title>Arduino Weebsite</title>");
        client.println("</head><body>");
        client.println("This is my fist webside!");
        client.println("<br>Calldawn 22.03.31");
        client.println("</body></html>");
        //內容
        break;
      }
    }
    delay(1);
    client.stop();
  }
}
