#include "arduino_final.h"


// definir les objets de type Servo pour les servomoteurs
Servo servoBras, servoAvantBras, servoTourneBras, servoRotationBras, servoInclinaisonPince, servoRotationPince, servoPince; // création de l'objet "servo"


static uint8_t time;
  
servomoteur structPince;
servomoteur structRotationPince;
servomoteur structInclinaisonPince;
servomoteur structRotationBras;
servomoteur structTourneBras;
servomoteur structAvantBras;
servomoteur structBras;

void data_servomotor() {

    uint8_t tab_servo[7];
    // Ecrire sur moniteur données servomoteurs

    //Envoyer données servomoteurs
    Serial.write('D');

    tab_servo[0] = servoPince.read();
    tab_servo[1] = servoRotationPince.read();
    tab_servo[2] = servoInclinaisonPince.read();
    tab_servo[3] = servoRotationBras.read();
    tab_servo[4] = servoTourneBras.read();
    tab_servo[5] = servoAvantBras.read();
    tab_servo[6] = servoBras.read();

    //string

    for(int i=0; i<7; i++){
      Serial.println(tab_servo[i]);
      Serial.write(',');
    }
}


void order(String command) {

    /***************************** Servomoteurs *******************************/
    if (command == "servomoteur") data_servomotor();

    /***************************** Réinitialisation *******************************/
    else if(command == "rei"){
      reset(&structPince, 20);
      reset(&structRotationPince, 60);
      reset(&structInclinaisonPince, 45);
      reset(&structRotationBras, 90);
      reset(&structTourneBras, 90);
      reset(&structAvantBras, 50);
      reset(&structBras, 110);
    }

    /***************************** Pince **************************************/
    else if (command == "sp") {
        Serial.println("(Arduino) action  : STOP pince");
        structPince.etat = 0;
    }
    else if (command == "op") {
        Serial.println("(Arduino) action  : OUVRE pince");
        structPince.etat = 1;
    } 
    else if (command == "cl") {
        Serial.println("(Arduino) action  : FERME pince");
        structPince.etat = -1;   
    }


    /***************************** Rotation Pince **************************************/
    else if (command == "srP") {
        structRotationPince.etat = 0;
        //Serial.println("action  : STOP ROTATION");
    } else if (command == "rPG") { //160 max 0 min
        structRotationPince.etat = 1;
        //Serial.println("action  : ROTATION pince droite");
    } else if (command == "rPD") {
        structRotationPince.etat = -1;
        //Serial.println("action  : ROTATION pince gauche");
    }


    /***************************** Inclinaison Pince **************************************/
    else if (command == "stop_inclinaisonPince") {
        structInclinaisonPince.etat = 0;
        Serial.println("action  : STOP INCLINE");
    } else if (command == "inclinaisonPinceAvant") { //180 max 0 min possède des problèmes
        structInclinaisonPince.etat = 1;
        Serial.println("action  : INCLINE pince avant");
    } else if (command == "inclinaisonPinceArriere") {
        structInclinaisonPince.etat = -1;
        Serial.println("action  : INCLINE pince arrière");
    }


    /***************************** Rotation Bras **************************************/
    else if (command == "stop_rotationBras") { //35 170gauche
        structRotationBras.etat = 0;
        Serial.println("action  : STOP ROTATION bras");
    } else if (command == "rotationBrasGauche") { //35 170gauche
        structRotationBras.etat = 1;
        Serial.println("action  : rotation bras gauche");
    } else if (command == "rotationBrasDroite") {
        structRotationBras.etat = -1;
        Serial.println("action  : rotation bras droite");
    }


    /***************************** Tourne Bras **************************************/
    else if (command == "stB") {
        structTourneBras.etat = 0;
        Serial.println("action  : STOP TOURNE bras");
    } else if (command == "tBG") {
        structTourneBras.etat = 1;
        Serial.println("action  : tourne bras gauche");
    } else if (command == "tBD") {
        structTourneBras.etat = -1;
        Serial.println("action  : tourne bras droite");
    }
  

    /***************************** Control Bras **************************************/
    else if(command == "stop_avantBras"){
      structAvantBras.etat = 0;
      //Serial.println(structAvantBras.servo.read());
      Serial.println("action  : STOP AVANT BRAS");
    }else if(command == "leverAvantBras"){
      structAvantBras.etat = 1;
      //Serial.println(structAvantBras.servo.read());
      Serial.println("action  : lever avant bras");
    }else if(command == "descendreAvantBras"){
      structAvantBras.etat -1;
      //Serial.println(structAvantBras.servo.read());
      Serial.println("action  : descendre avant bras");
    }
    /*Serial.println("Bras Secondaire");
    Serial.println(servoBrasSecondaire.read());*/


    else if(command == "stop_bras"){
      structBras.etat = 0;
      //Serial.println(structBras.servo.read());
      Serial.println("action  : STOP BRAS");
    }else if(command == "descendreBras"){
      structBras.etat = 1;
      //Serial.println(structBras.servo.read());
      Serial.println("action  : descendre bras");
    }else if(command == "leverBras"){
      structBras.etat = -1;
      //Serial.println(structBras.servo.read());
      Serial.println("action  : lever bras");
    }
    /*Serial.println("Bras Principal");
    Serial.println(servoBrasPrincipal.read());*/
}



void setup() {

    // Communication série // serie pour la com
    Serial.begin(115200); // serie de l'arduino
    pinMode(13, OUTPUT);

    structPince = begin(servoPince, 20, PIN_PINCE, 8, 76); // pince
    structRotationPince = begin(servoRotationPince, 60, PIN_ROTATION_PINCE, 10, 170); // rotation de la pince
    structInclinaisonPince = begin(servoInclinaisonPince, 45, PIN_INCLINAISON_PINCE, 5, 175); // inclinaison de la pince (20-160)

    structRotationBras = begin(servoRotationBras, 90, PIN_ROTATION_BRAS, 35, 170);
    structTourneBras = begin(servoTourneBras, 90, PIN_TOURNE_BRAS, 10, 170);
    structAvantBras = begin(servoAvantBras, 50, PIN_AVANT_BRAS, 10, 80);
    structBras = begin(servoBras, 110, PIN_BRAS, 90, 150);

    //Envoyer données sur les servomoteurs à l'initialisation
    delay(2000);
    data_servomotor();
    delay(1000);
}

void receive() {

  static char letter;
  static String command;
  
  if (Serial.available()) {

    //Serial.print("Char received : ");
    letter = Serial.read();
    Serial.println(letter);

    if (letter == '\n') {
      command = command + '\0';
      //Serial.println("(Arduino) command : " + command);
      order(command);
      command = "";
    } else {
      command = command + letter;
    }
    time = 0;
    //digitalWrite(13, HIGH);

  } else {
    delay(80);
    time++;
  }
  //digitalWrite(13, LOW);
}


void loop() {

    receive();

    move(&structPince);
    move(&structRotationPince);
    move(&structInclinaisonPince);
    move(&structRotationBras);
    move(&structTourneBras);
    move(&structAvantBras);
    move(&structBras);

    if (time == 200) {
        data_servomotor();
        time = 0;
    }
}
