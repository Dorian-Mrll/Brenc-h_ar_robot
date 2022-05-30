#include <Arduino.h>
#include <WiFi.h>
#include <FirebaseESP32.h>

//Provide the token generation process info.
#include "addons/TokenHelper.h"
//Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"

// Insert your network credentials
#define WIFI_SSID "Mi"
#define WIFI_PASSWORD "gribouille2"

// Insert Firebase project API Key
#define API_KEY "AIzaSyDBsWChFAR-afuQAjqJgUXaDiXvafazYWE"

// Insert Authorized Email and Corresponding Password
#define USER_EMAIL "nairod.bzh@gmail.com"
#define USER_PASSWORD "123456789"

// Insert RTDB URLefine the RTDB URL
#define DATABASE_URL "https://esp32-31ba2-default-rtdb.europe-west1.firebasedatabase.app" 


String readString;
String incomingString;

uint8_t tab_servo_in[14];
const int NB_SERVOMOTOR = 7;

//Define Firebase Data object
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

FirebaseJsonArray json;
FirebaseJsonArray jsonArray;

// Variable to save USER UID
String uid;

unsigned long sendDataPrevMillis = 0;
String command;


void servomotor(){  //uint8_t
  for(int i=0; i<NB_SERVOMOTOR; i++){
    int servomotor = Serial.read();
    int degree = Serial.read();
    if(servomotor > 0 && servomotor < NB_SERVOMOTOR+1){
      Serial.println(String("Servomotor ") + servomotor);
      Serial.println(String("Degree ") + degree);  
    }
    delay(50);
  }
}

void writeString(String command) { // Used to serially push out a String with Serial.write()

  Serial.flush();
  for(int i=0; i<command.length(); i++){
    //Serial.print("Sent char : ");
    Serial.write(command.charAt(i));
    //Serial.println("");
    //mySerial.write(command.charAt(i));
    //delay(100);
  }
  //Serial.print  ("Sent char end : ");
  Serial.write('\n');
  //Serial.println("");
  //delay(200);
}


void setup() {
  //Serial2.begin(9600, SERIAL_8N1, RXp2, TXp2);
  Serial.begin(115200);
  pinMode(2, OUTPUT);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  //Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    //Serial.print(".");
    delay(1000);
  }
  //Serial.println(WiFi.localIP());
  //Serial.println();

  // Assign the api key (required)
  config.api_key = API_KEY;

  // Assign the user sign in credentials
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;

  // Assign the RTDB URL (required)
  config.database_url = DATABASE_URL;

  Firebase.reconnectWiFi(true);
  fbdo.setResponseSize(4096);

  // Assign the callback function for the long running token generation task
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h

  // Assign the maximum retry of token generation
  config.max_token_generation_retry = 5;

  // Initialize the library with the Firebase authen and config
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

  // Getting the user UID might take a few seconds
  //Serial.println("Getting User UID");
  while ((auth.token.uid) == "") {
    //Serial.print('.');
    delay(1000);
  }
  // Print user UID
  /*uid = auth.token.uid.c_str();
  Serial.print("User UID: ");
  Serial.print(uid);*/
}


void erase(int taille){
  for(int i=0; i<taille; i++){
    Firebase.RTDB.deleteNode(&fbdo, "/commandes/" + String(i));
  }
}


int cpt=0,temp=0;
bool del=false;

void loop() {


  //Serial.println('t');

  //Serial.println(50);

  
  del=false;

  delay(1000);

  // recevoir données de l'Arduino (angles servomoteurs)
  /*if (Serial.available() && Serial.read() == 'S') {
      //Serial.println("(ESP32) Received data from Arduino : ");


        for(int i=0; i<14; i++){
        digitalWrite(2, 1);
        
        int x = Serial.parseInt();
        switch(i){
          case 1:
            Firebase.RTDB.setInt(&fbdo, "/servomoteurs/ServoPince", x);
            break;
          case 3:
            Firebase.RTDB.setInt(&fbdo, "/servomoteurs/ServoRotationPince", x);
            break;
          case 5:
            Firebase.RTDB.setInt(&fbdo, "/servomoteurs/ServoInclinaison", x);
            break;
          case 7:
            Firebase.RTDB.setInt(&fbdo, "/servomoteurs/ServoRotationBras", x);
            break;
          case 9:
            Firebase.RTDB.setInt(&fbdo, "/servomoteurs/ServoTournePince", x);
            break;
          case 11:
            Firebase.RTDB.setInt(&fbdo, "/servomoteurs/ServoBrasPrincipal", x);
            break;
        }
                
        
        //Serial.print(x);
        //Serial.print(",");
        delay(50);
        digitalWrite(2, 0);
      }    
  }else{*/
    //Serial.println("no data from Arduino");
    if (Firebase.ready() && (millis() - sendDataPrevMillis > 750 || sendDataPrevMillis == 0)) {
    sendDataPrevMillis = millis();
  
    Firebase.RTDB.getArray(&fbdo, "/commandes/", &jsonArray);
    FirebaseJsonArray &sousArr = fbdo.jsonArray();
    FirebaseJsonData jsonData;
    sousArr.get(jsonData, cpt);

    String command = jsonData.stringValue;
    //Serial.println(cpt);
    
    if(command == NULL){
      temp=cpt;
      cpt = 0;
      del=true;
      if(del) erase(temp);
      Firebase.RTDB.setInt(&fbdo, "/compteur/", 0);
    }
    else {
      delay(50);
      //Serial.println(command);
      
      writeString(command);
      //Firebase.RTDB.deleteNode(&fbdo, "/commandes/" + String(cpt));
      cpt++;
    }
    }
  //}
}
    

    
