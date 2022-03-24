void setup() {
  // put your setup code here, to run once:
  Serial.println("Welcome to Arduino!");
  pinMode(A3,OUTPUT);
  pinMode(A4,OUTPUT);
  pinMode(8, OUTPUT);
  Serial.begin(9600);
}
int light;
int lf = 0;
boolean lit = 0;
void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(A3, HIGH);
  digitalWrite(A4, LOW);
  light = analogRead(A2);
  if (light-lf>500||lf-light>500) {
     lit = !lit;
     if (lit==1) {
      Serial.println("Light On!");
     } else {
      Serial.println("Lights Are Off!");
     }
  } else {
    lit = lit;
  } 
  lf = light;
  digitalWrite(8, lit);
}
