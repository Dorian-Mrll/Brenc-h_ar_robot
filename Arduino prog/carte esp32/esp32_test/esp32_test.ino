   void setup(){
    Serial.begin(115200);
    pinMode(2, OUTPUT);
}

void loop(){
  digitalWrite(2, HIGH);
  Serial.print('A');
  delay(1000);  
  Serial.print('B');
  digitalWrite(2, LOW);
  delay(1000);
}   
