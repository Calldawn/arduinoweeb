void setup() {
  // put your setup code here, to run once:
pinMode(2, INPUT);
pinMode(13, OUTPUT);
}
boolean val;
void loop() {
  // put your main code here, to run repeatedly:
  val = digitalRead(2);
  
  digitalWrite(13, HIGH);
}
