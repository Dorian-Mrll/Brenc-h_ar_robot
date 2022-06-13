uint8_t tab_servo[4] = {1,20,2,40};
int c=0;
String res;

void setup(){
    Serial.begin(115200);
    pinMode(13, OUTPUT);
}

void loop(){
  c++;
  
  // Send Arduino
  
  //digitalWrite(13, HIGH);
  Serial.write('E');
  delay(1000);

  if(c==15){
    Serial.write('S');
    for(int i=0; i<sizeof(tab_servo)/sizeof(uint8_t); i++){
      Serial.print(tab_servo[i]);
      Serial.print(',');
    }
    c=0;
  }

  // Receive Arduino
  
  if(Serial.available()>0) {
    char c = Serial.read();
    //if(c=='A') digitalWrite(13, LOW);

    if(c=='C'){
      digitalWrite(13, HIGH);
      res = Serial.readStringUntil('\n');
      Serial.println(res);
      delay(50);
      digitalWrite(13, LOW);
    }
  }
  delay(1000);
}   
