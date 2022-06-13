int c=0;

void setup(){
    Serial.begin(115200);
    pinMode(2, OUTPUT);
}

void loop(){
  c++;
  // Send ESP
  
  //digitalWrite(2, 1);
  Serial.write('A');
  delay(1000);

  if(c==25){
    Serial.write('C');
    Serial.write("Commandeslongue");
  c=0;
  }


  // Receive ESP
  
  if(Serial.available()>0) {
    char c = Serial.read();
    //if(c=='E') digitalWrite(2, 0);

    if(c=='S'){
      for(int i=0; i<4; i++){
        digitalWrite(2, 1);
        int x = Serial.parseInt();
        Serial.println(x);
        Serial.print(",");
        delay(50);
        digitalWrite(2, 0);
      }
    }
  }
  delay(1000);
}
