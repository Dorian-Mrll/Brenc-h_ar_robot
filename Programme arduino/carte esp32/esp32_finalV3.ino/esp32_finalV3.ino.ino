#include <Arduino.h>
#include <WiFi.h>
#include <FirebaseESP32.h>

//Provide the token generation process info.
#include "addons/TokenHelper.h"
//Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"

#define WIFI_SSID "Mi"
#define WIFI_PASSWORD "gribouille2"

#define API_KEY "AIzaSyDBsWChFAR-afuQAjqJgUXaDiXvafazYWE"

// Insert Authorized Email and Corresponding Password
#define USER_EMAIL "nairod.bzh@gmail.com"
#define USER_PASSWORD "123456789"

// Insert RTDB URLefine the RTDB URL
#define DATABASE_URL "https://esp32-31ba2-default-rtdb.europe-west1.firebasedatabase.app" 

//Use multiple FirebaseData may lead to low memory and reboot from exception error

//Définit les objets de données de FirebaseESP32
FirebaseData firebaseData1;
FirebaseData firebaseData2;

FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis;


enum command { OUVRE_PINCE=1, FERME_PINCE, STOP_PINCE, 
ROTATION_GAUCHE_PINCE, ROTATION_DROITE_PINCE, STOP_ROTATION_PINCE, 
INCLINAISON_AVANT_PINCE, INCLINAISON_ARRIERE_PINCE, STOP_INCLINAISON_PINCE, 
TOURNE_GAUCHE_BRAS, TOURNE_DROITE_BRAS, STOP_TOURNE_BRAS, 
LEVER_AVANTBRAS, BAISSER_AVANTBRAS, STOP_AVANTBRAS,
ROTATION_GAUCHE_BRAS, ROTATION_DROITE_BRAS, STOP_ROTATION_BRAS,
LEVER_BRAS, BAISSER_BRAS, STOP_BRAS, REINITIALISER, SERVOMOTEUR };



void writefirebase(const char* s){
 
  uint8_t a,b,c,d,e,f,g;
  sscanf(s, "%d,%d,%d,%d,%d,%d,%d", &a, &b, &c, &d, &e, &f, &g);

  FirebaseJson json;
  json.setJsonData("{\"Pince\":{\"Pince\":"+String(a)+",\"Rotation\":"+String(b)+",\"Inclinaison\":"+String(c)+"}}");

  FirebaseJson json2;
  json2.setJsonData("{\"Bras\":{\"Rotation\":"+String(d)+",\"Tourne\":"+String(e)+",\"AvantBras\":"+String(f)+",\"Bras\":"+String(g)+"}}");



  ///Firebase.RTDB.setInt(&firebaseData1, "/Servomoteurs/Pince/Pince", a);
  Firebase.updateNode(firebaseData1, "/Servomoteurs", json);
  Firebase.updateNode(firebaseData1, "/Servomoteurs", json2);
  //Firebase.RTDB.setInt(&firebaseData1, "/Servomoteurs/Pince/Rotation", b);
  /*Firebase.RTDB.setInt(&firebaseData1, "/Servomoteurs/Pince/Inclinaison", c);*/
  /*Firebase.RTDB.setInt(&firebaseData1, "/Servomoteurs/Bras/Rotation", d);
  Firebase.RTDB.setInt(&firebaseData1, "/Servomoteurs/Bras/Tourne", e);
  Firebase.RTDB.setInt(&firebaseData1, "/Servomoteurs/Bras/Bras", f);
  Firebase.RTDB.setInt(&firebaseData1, "/Servomoteurs/Bras/AvantBras", g);*/

}

void streamCallback(StreamData data){

  // Données disponibles sur le flux
  if (data.dataType() == "boolean"){
    if(data.dataPath() == "/Pince/ouvre"){
      if(data.boolData()){ Serial.write('#');  Serial.println(OUVRE_PINCE); }
      else { Serial.write('#'); Serial.println(STOP_PINCE); }
    }else if(data.dataPath() == "/Pince/ferme"){
      if(data.boolData()) { Serial.write('#'); Serial.println(FERME_PINCE); }
      else { Serial.write('#'); Serial.println(STOP_PINCE); }
    }
    
    else if(data.dataPath() == "/Pince/rotation_gauche"){
      if(data.boolData()) { Serial.write('#'); Serial.println(ROTATION_GAUCHE_PINCE); }
      else { Serial.write('#'); Serial.println(STOP_ROTATION_PINCE); }
    }else if(data.dataPath() == "/Pince/rotation_droite"){
      if(data.boolData()) { Serial.write('#'); Serial.println(ROTATION_DROITE_PINCE); }
      else { Serial.write('#'); Serial.println(STOP_ROTATION_PINCE); }
    }

    else if(data.dataPath() == "/Pince/inclinaison_avant"){
      if(data.boolData()) { Serial.write('#'); Serial.println(INCLINAISON_AVANT_PINCE); }
      else { Serial.write('#'); Serial.println(STOP_INCLINAISON_PINCE); }
    }else if(data.dataPath() == "/Pince/inclinaison_arriere"){
      if(data.boolData()) { Serial.write('#'); Serial.println(INCLINAISON_ARRIERE_PINCE); }
      else { Serial.write('#'); Serial.println(STOP_INCLINAISON_PINCE); }
    }

    else if(data.dataPath() == "/Bras/tourne_gauche"){
      if(data.boolData()) { Serial.write('#'); Serial.println(TOURNE_GAUCHE_BRAS); }
      else { Serial.write('#'); Serial.println(STOP_TOURNE_BRAS); }
    }else if(data.dataPath() == "/Bras/tourne_droite"){
      if(data.boolData()) { Serial.write('#'); Serial.println(TOURNE_DROITE_BRAS); }
      else { Serial.write('#'); Serial.println(STOP_TOURNE_BRAS); }
    }

    else if(data.dataPath() == "/Bras/lever_avant-bras"){
      if(data.boolData()) { Serial.write('#'); Serial.println(LEVER_AVANTBRAS); }
      else { Serial.write('#'); Serial.println(STOP_AVANTBRAS); }
    }else if(data.dataPath() == "/Bras/baisser_avant-bras"){
      if(data.boolData()) { Serial.write('#'); Serial.println(BAISSER_AVANTBRAS); }
      else { Serial.write('#'); Serial.println(STOP_AVANTBRAS); }
    }

    else if(data.dataPath() == "/Bras/rotation_gauche"){
      if(data.boolData()) { Serial.write('#'); Serial.println(ROTATION_GAUCHE_BRAS); }
      else { Serial.write('#'); Serial.println(STOP_ROTATION_BRAS); }
    }else if(data.dataPath() == "/Bras/rotation_droite"){
      if(data.boolData()) { Serial.write('#'); Serial.println(ROTATION_DROITE_BRAS); }
      else { Serial.write('#'); Serial.println(STOP_ROTATION_BRAS); }
    }

    else if(data.dataPath() == "/Bras/lever_bras"){
      if(data.boolData()) { Serial.write('#'); Serial.println(LEVER_BRAS); }
      else { Serial.write('#'); Serial.println(STOP_BRAS); }
    }else if(data.dataPath() == "/Bras/baisser_bras"){
      if(data.boolData()) { Serial.write('#'); Serial.println(BAISSER_BRAS); }
      else { Serial.write('#'); Serial.println(STOP_BRAS); }
    }

    else if(data.dataPath() == "/reinitialiser"){
      if(data.boolData()) { Serial.write('#'); Serial.println(REINITIALISER); writefirebase("20,45,60,90,90,50,110"); }
    }else if(data.dataPath() == "/servomoteur"){
      if(data.boolData()) { Serial.write('#'); Serial.println(SERVOMOTEUR); }
    }
  }
}


void streamTimeoutCallback(bool timeout)
{
  if(timeout){
    //Stream timeout occurred
    Serial.println("Stream timeout, resume streaming...");
  }  
}


void setup()
{

  Serial.begin(115200);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecté en WiFi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connecté avec l'IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();


  // Assigner identifiant base de données
  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;

  // Assigner identifiant utilisateur
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;


  // Initialize the library with the Firebase authen and config

  Firebase.reconnectWiFi(true);
  config.token_status_callback = tokenStatusCallback;
  
  
  Firebase.begin(&config, &auth);
 

  Firebase.setStreamCallback(firebaseData2, streamCallback, streamTimeoutCallback);

  if (!Firebase.beginStream(firebaseData2, "/Commandes"))
  {
    Serial.println("------Impossible de commencer la connexion du flux 1------");
    Serial.println(firebaseData2.errorReason());
  }
}




void loop()
{
    // On récupère le string qui contient toutes les angles des servomoteurs et qui commence par le TAG dollar
    // puis on appel la fonction writefirebase qui va permettrre d'ecrire et donc de mettre à jour les angles des servomoteurs dans la base de donnée
    if(Serial.available() && Serial.read() == '$') {

      String incomming = Serial.readString();
      char copy[incomming.length()+1];
      incomming.toCharArray(copy, incomming.length()+1);
      writefirebase(copy);
    }

    // on vérifie que la base est bien connecté et on vérifie tous les 10 sec qu'on est bien connecté au WiFi
    // sinon on se reconnecte et on repasse la valeur de vérification de connection à true
    /*if (Firebase.ready() && (millis() - sendDataPrevMillis > 750 || sendDataPrevMillis == 0)) {
      sendDataPrevMillis = millis();

      if(WiFi.status() != WL_CONNECTED){
        WiFi.disconnect();
        WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
      }
    }
    Firebase.RTDB.setBool(&firebaseData1, "/ESP32/WiFi", true);*/
}
