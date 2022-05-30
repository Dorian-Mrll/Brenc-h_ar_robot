void setup(){
    Serial.begin(115200);
    pinMode(13, OUTPUT);
}

void loop(){
  if(Serial.available()>0) {
    char c = Serial.read();
    if(c=='A') digitalWrite(13, 1);
    if(c=='B') digitalWrite(13, 0);
  }
  delay(10);
}
