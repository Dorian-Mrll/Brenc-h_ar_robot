#include <Servo.h>

#define PIN_PINCE 13
#define PIN_ROTATION_PINCE 12
#define PIN_INCLINAISON_PINCE 11
#define PIN_ROTATION_BRAS 9
#define PIN_TOURNE_BRAS 8
#define PIN_AVANT_BRAS 6
#define PIN_BRAS 5


Servo servoBras, servoAvantBras, servoTourneBras, servoRotationBras, servoInclinaisonPince, servoRotationPince, servoPince; // création de l'objet "servo"
char letter;
String command;
int time = 0;
uint8_t tab_servo[14];

typedef struct servomoteur {
    Servo servo;
    int etat;
    int angle;
    int pin;
    int min;
    int max;
}
servomoteur;


servomoteur structPince;
servomoteur structRotationPince;
servomoteur structInclinaisonPince;
servomoteur structRotationBras;
servomoteur structTourneBras;
servomoteur structAvantBras;
servomoteur structBras;




// .h
// fonctions utilisées
servomoteur begin(Servo & obj, int angle, int pin);
void data_servomotor();
void order(String commande);
void receive();
void move(struct servomoteur * servo);


servomoteur begin(Servo & obj, int angle, int pin, int min, int max) {

    servomoteur res_servo = {obj,0,angle,pin,min,max};
  
    res_servo.servo.attach(res_servo.pin); // attache le servo au pin spécifié
    res_servo.servo.write(res_servo.angle);

    return res_servo;
}


void data_servomotor() {

    // Ecrire sur moniteur données servomoteurs
    /*Serial.println("(Arduino)Send data servomoteur");
    Serial.println("(Servo1) angle : " + String(servoPince.read()));
    Serial.println("(Servo2) angle : " + String(servoRotationPince.read()));
    Serial.println("(Servo3) angle : " + String(servoInclinaisonPince.read()));
    Serial.println("(Servo4) angle : " + String(servoRotationBras.read()));
    Serial.println("(Servo5) angle : " + String(servoTourneBras.read()));
    Serial.println("(Servo6) angle : " + String(servoAvantBras.read()));
    Serial.println("(Servo7) angle : " + String(servoBras.read()));*/

    //Envoyer données servomoteurs
    Serial.write('D');

    tab_servo[0] = 1;
    tab_servo[1] = servoPince.read();
    tab_servo[2] = 2;
    tab_servo[3] = servoRotationPince.read();
    tab_servo[4] = 3;
    tab_servo[5] = servoInclinaisonPince.read();
    tab_servo[6] = 4;
    tab_servo[7] = servoRotationBras.read();
    tab_servo[8] = 5;
    tab_servo[9] = servoTourneBras.read();
    tab_servo[10] = 6;
    tab_servo[11] = servoAvantBras.read();
    tab_servo[12] = 7;
    tab_servo[13] = servoBras.read();


    for(int i=0; i<14; i++){
      Serial.println(tab_servo[i]);
      Serial.write(',');
    }
}


void order(String command) {


    /***************************** Servomoteurs *******************************/
    if (command == "(Arduino) servomoteur") data_servomotor();


    /***************************** Pince **************************************/
    if (command == "stop_pince") {
        Serial.println("(Arduino) action  : STOP pince");
        structPince.etat = 0;
    }
    else if (command == "open") {
        Serial.println("(Arduino) action  : OUVRE pince");
        structPince.etat = 1;
    } 
    else if (command == "close") {
        Serial.println("(Arduino) action  : FERME pince");
        structPince.etat = -1;   
    }


    /***************************** Rotation Pince **************************************/
    if (command == "stop_rotationPince") {
        structRotationPince.etat = 0;
        Serial.println("action  : STOP ROTATION");
    } else if (command == "rotationPinceDroite") { //160 max 0 min
        structRotationPince.etat = 1;
        Serial.println("action  : ROTATION pince droite");
    } else if (command == "rotationPinceGauche") {
        structRotationPince.etat = -1;
        Serial.println("action  : ROTATION pince gauche");
    }


    /***************************** Inclinaison Pince **************************************/
    if (command == "stop_inclinaisonPince") {
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
    if (command == "stop_rotationBras") { //35 170gauche
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
    if (command == "stop_tourneBras") {
        structTourneBras.etat = 0;
        Serial.println("action  : STOP TOURNE bras");
    } else if (command == "tourneBrasGauche") {
        structTourneBras.etat = 1;
        Serial.println("action  : tourne bras gauche");
    } else if (command == "tourneBrasDroite") {
        structTourneBras.etat = -1;
        Serial.println("action  : tourne bras droite");
    }
  

    /***************************** Control Bras **************************************/
    if(command == "stop_avantBras"){
      structAvantBras.etat = 0;
      Serial.println(structAvantBras.servo.read());
      Serial.println("action  : STOP AVANT BRAS");
    }else if(command == "leverAvantBras"){
      structAvantBras.etat = 1;
      Serial.println(structAvantBras.servo.read());
      Serial.println("action  : lever avant bras");
    }else if(command == "descendreAvantBras"){
      structAvantBras.etat -1;
      Serial.println(structAvantBras.servo.read());
      Serial.println("action  : descendre avant bras");
    }
    /*Serial.println("Bras Secondaire");
    Serial.println(servoBrasSecondaire.read());*/


    if(command == "stop_bras"){
      structBras.etat = 0;
      Serial.println(structBras.servo.read());
      Serial.println("action  : STOP BRAS");
    }else if(command == "descendreBras"){
      structBras.etat = 1;
      Serial.println(structBras.servo.read());
      Serial.println("action  : descendre bras");
    }else if(command == "leverBras"){
      structBras.etat = -1;
      Serial.println(structBras.servo.read());
      Serial.println("action  : lever bras");
    }
    /*Serial.println("Bras Principal");
    Serial.println(servoBrasPrincipal.read());*/
}


void setup() {

    // Communication série // serie pour la com
    Serial.begin(115200); // serie de l'arduino
    pinMode(13, OUTPUT);

    structPince = begin(servoPince, 20, PIN_PINCE, 8, 80); // pince
    structRotationPince = begin(servoRotationPince, 60, PIN_ROTATION_PINCE, 10, 170); // rotation de la pince
    structInclinaisonPince = begin(servoInclinaisonPince, 45, PIN_INCLINAISON_PINCE, 5, 175); // inclinaison de la pince (20-160)

    structRotationBras = begin(servoRotationBras, 90, PIN_ROTATION_BRAS, 35, 170);
    structTourneBras = begin(servoTourneBras, 90, PIN_TOURNE_BRAS, 10, 170);

    structAvantBras = begin(servoAvantBras, 50, PIN_AVANT_BRAS, 10, 80); //(10-80)
    structBras = begin(servoBras, 110, PIN_BRAS, 90, 150);

    //Serial.flush();
    //Envoyer données sur les servomoteurs à l'initialisation
    //data_servomotor();
    delay(2000);
    //Serial.println("Start robot !");
    Serial.flush();
}


void receive() {

    if (Serial.available()) {
        
        //Serial.print("Char received : ");
        letter = Serial.read();
        //Serial.println(letter);

        if (letter == '\n') {
            command = command + '\0';
            Serial.println("(Arduino) command : " + command);
            //Serial.print("command : ");
            //Serial.println(command);
            order(command);
            command = "";
        } else {
            command = command + letter;
        }
        time=0;
        digitalWrite(13, HIGH);
        
    } else {
        delay(80);
        time++;
    }
    digitalWrite(13, LOW);
}



// permet de changer la position du servomoteur
void move(struct servomoteur * servo) {
    delay(10);
    if (servo->etat == 1 && servo->servo.read() <= servo->max){
      if(servo->servo.read() > servo->max-10) delay(80);
      servo -> angle = servo -> angle + 3;
    }
    else if(servo->etat == -1 && servo->servo.read() >= servo->min) { 
      if(servo->servo.read() < servo->min+10) delay(80);
      servo -> angle = servo -> angle - 3;
    }
    servo -> servo.write(servo -> angle);
}


void loop() {

    receive();

    
    if (structPince.etat != 0) move(&structPince);
    if(structRotationPince.etat != 0) move(&structRotationPince);
    if(structInclinaisonPince.etat != 0) move(&structInclinaisonPince);
    if(structRotationBras.etat !=0)  move(&structRotationBras);
    if(structTourneBras.etat !=0) move(&structTourneBras);
    if(structAvantBras.etat !=0) move(&structAvantBras);
    if(structBras.etat !=0) move(&structBras);


    if (time == 200) {
        data_servomotor();
        time = 0;
    }
}