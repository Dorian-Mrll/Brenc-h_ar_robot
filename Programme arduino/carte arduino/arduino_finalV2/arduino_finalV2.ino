#include "arduino_finalV2.h"


// definir les objets de type Servo pour les servomoteurs
Servo servoBras, servoAvantBras, servoTourneBras, servoRotationBras, servoInclinaisonPince, servoRotationPince, servoPince; // création de l'objet "servo"

  
servomoteur structPince;
servomoteur structRotationPince;
servomoteur structInclinaisonPince;
servomoteur structRotationBras;
servomoteur structTourneBras;
servomoteur structAvantBras;
servomoteur structBras;

static uint8_t time;

void data_servomotor() {

    // Ecrire sur moniteur données servomoteurs

    //Envoyer données servomoteurs
    String res = '$' + (String)servoPince.read() + "," + (String)servoRotationPince.read() + "," + (String)servoInclinaisonPince.read() + "," + (String)servoRotationBras.read() + "," + (String)servoTourneBras.read() + "," + (String)servoAvantBras.read() + "," + (String)servoBras.read();
    Serial.println(res);
}


// modidifie l'etat courant d'un servomoteut en fonction de la commande a effectuer
void order(int command) {

    switch(command){
    /***************************** Pince **************************************/
    case 3 :
        structPince.etat = 0;
        Serial.println("(Arduino) action  : STOP pince");
        break;
    case 1 :
        structPince.etat = 1;
        Serial.println("(Arduino) action  : OUVRE pince");
        break;
    case 2 :
        structPince.etat = -1;
        Serial.println("(Arduino) action  : FERME pince");
        break;


    /***************************** Rotation Pince **************************************/
    case 6 :
        structRotationPince.etat = 0;
        Serial.println("(Arduino) action  : STOP ROTATION");
        break;
    case 4 :
        structRotationPince.etat = 1;
        Serial.println("(Arduino) action  : ROTATION pince droite");
        break;
    case 5 :
        structRotationPince.etat = -1;
        Serial.println("(Arduino) action  : ROTATION pince gauche");
        break;


    /***************************** Inclinaison Pince **************************************/
    case 9 :
        structInclinaisonPince.etat = 0;
        Serial.println("(Arduino) action  : STOP INCLINE");
        break;
    case 7 :
        structInclinaisonPince.etat = 1;
        Serial.println("(Arduino) action  : INCLINE pince avant");
        break;
    case 8 :
        structInclinaisonPince.etat = -1;
        Serial.println("(Arduino) action  : INCLINE pince arrière");
        break;


    /***************************** Tourne Bras **************************************/
    case 12 :
        structTourneBras.etat = 0;
        Serial.println("(Arduino) action  : STOP TOURNE bras");
        break;
    case 10 :
        structTourneBras.etat = 1;
        Serial.println("(Arduino) action  : tourne bras gauche");
        break;
    case 11 :
        structTourneBras.etat = -1;
        Serial.println("(Arduino) action  : tourne bras droite");
        break;
  

    /***************************** Control Bras **************************************/
    case 15 :
        structAvantBras.etat = 0;
        Serial.println("(Arduino) action  : STOP AVANT BRAS");
        break;
    case 13 :
        structAvantBras.etat = -1;
        Serial.println("(Arduino) action  : baisser avant bras");
        break;
    case 14 :
        structAvantBras.etat = 1;
        Serial.println("(Arduino) action  : lever avant bras");
        break;


    case 21 :
        structBras.etat = 0;
        Serial.println("(Arduino) action  : STOP BRAS");
        break;
    case 20 :
        structBras.etat = 1;
        Serial.println("(Arduino) action  : baisser bras");
        break;
    case 19 :
        structBras.etat = -1;
        Serial.println("(Arduino) action  : lever bras");
        break;


    /***************************** Rotation Bras **************************************/
    case 18 :
        structRotationBras.etat = 0;
        Serial.println("(Arduino) action  : STOP ROTATION bras");
        break;
    case 16 :
        structRotationBras.etat = 1;
        Serial.println("(Arduino) action  : rotation bras gauche");
        break;
    case 17 :
        structRotationBras.etat = -1;
        Serial.println("(Arduino) action  : rotation bras droite");
        break;


    /***************************** Réinitialisation *******************************/
    case 22 :
        reset(&structPince, 20);
        reset(&structRotationPince, 60);
        reset(&structInclinaisonPince, 45);
        reset(&structRotationBras, 90);
        reset(&structTourneBras, 90);
        reset(&structAvantBras, 50);
        reset(&structBras, 110);
        break;
    

    /***************************** Servomoteurs *******************************/
    case 23 :
        data_servomotor();
        break;

    default :
        Serial.println("(Arduino) action  : commande non reconnu");
    }
}


void receive() {

  static char letter;
  static String command;
  
  if (Serial.available()) {

    Serial.print("Char received : ");
    letter = Serial.read();
    Serial.println(letter);

    if (letter == '\n') {
      //Serial.println("(Arduino) command : " + command);

      
      if(command.charAt(0) == '#') {
        int temp = command.substring(1).toInt();
        order(temp);
      }
      
      command = "";
    } else {
      command = command + letter;
    }
    time = 0;

  }
  else {
    delay(30);//vitesse d'execution 80
    time++;
  }
}


void setup() {

    // Communication série // serie pour la com
    Serial.begin(115200); // serie de l'arduino
    pinMode(13, OUTPUT);

    structPince = begin(servoPince, 20, PIN_PINCE, 4, 76); // pince
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


static uint8_t v1=1, v2=1, v3=1, v4=1, v5=1, v6=1, v7 = 1;

void loop() {

    receive();

    move(&structPince, v1);
    move(&structRotationPince, v2);
    move(&structInclinaisonPince, v3);
    move(&structRotationBras, v4);
    move(&structTourneBras, v5);
    move(&structAvantBras, v6);
    move(&structBras, v7);

    if (time == 200) {
        data_servomotor();
        time = 0;
    }
}
