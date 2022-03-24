#include <DHT.h>
DHT dht(A1, DHT11);//jhgfhtgfkfkyufkgfjhgfjhgfjhgfjhgfjgfjgfj
int testNumber = 0;
void setup() {
// put your setup code here, to run once:
  Serial.begin(9600);
  dht.begin();
  pinMode(A0, OUTPUT);
  pinMode(A2, OUTPUT);
  Serial.println("Welcome to Arduino!");
}
void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(A0, LOW);
  digitalWrite(A2, HIGH);
  if(Serial.available()){
    Serial.print("Temperature (c): ");
    Serial.println((float)dht.readTemperature(),2);
    Serial.print("Humidity (%): ");
    Serial.println((float)dht.readHumidity(),2);
    testNumber++;
    Serial.println(testNumber);
  }
  while(Serial.available()){
    Serial.read();    
  }
}
