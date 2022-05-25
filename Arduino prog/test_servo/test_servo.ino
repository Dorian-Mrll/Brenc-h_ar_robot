#include "Servo.h"

Servo servoBrasPrincipal, servoBrasSecondaire, servoTourneBras, servoRotationBras, servoInclinaisonPince, servoRotationPince, servoPince; // création de l'objet "servo"
int i1, i2, t, rb, i, rp, p;

void ordre(char commande) {
  
      /***************************** Pince **************************************/
      
      if(commande == 'P'){
        p = p+5;
        servoPince.write(p); // demande au servo de se déplacer à cette position
        Serial.println("OUVRE pince");
      }else if(commande == 'p'){
        p = p-5;
        servoPince.write(p);
        Serial.println("FERMER pince");
      }
      //Serial.println(servoPince.read());


      /***************************** Rotation Pince **************************************/

      if(commande == 'R'){ //160 max 0 min
        rp = rp+5;
        servoRotationPince.write(rp);
        Serial.println("rotation pince droite");
      }else if(commande == 'r'){
        rp = rp-5;
        servoRotationPince.write(rp);
        Serial.println("rotation pince gauche");
      }
      /*Serial.println("Rotation");
      Serial.println(servoRotationPince.read());*/


      /***************************** Inclinaison Pince **************************************/

      if(commande == 'I'){ //180 max 0 min possède des problèmes
        i = i+5;
        servoInclinaisonPince.write(i);
        Serial.println("incline pince avant");
      }else if(commande == 'i'){
        i = i-5;
        servoInclinaisonPince.write(i);
        Serial.println("incline pince arrière");
      }
      /*Serial.println("Inclinaison");
      Serial.println(servoInclinaisonPince.read());*/


      /***************************** Rotation Bras **************************************/

      if(commande == 'Y'){ //35 170gauche
        rb = rb+5;
        servoRotationBras.write(rb);
        Serial.println("rotation bras gauche");
      }else if(commande == 'y'){
        rb = rb-5;
        servoRotationBras.write(rb);
        Serial.println("rotation bras droite");
      }
      //Serial.println(commande);
      //Serial.println(servoRotationBras.read());
      


      /***************************** Tourne Bras **************************************/
      
      if(commande == 'T'){
        t = t+5;
        servoTourneBras.write(t);
        Serial.println("tourne bras gauche");
      }else if(commande == 't'){
        t = t-5;
        servoTourneBras.write(t);
        Serial.println("tourne bras droite");
      }
      //Serial.println(commande);
      //Serial.println(servoTourneBras.read());



      /***************************** Control Bras **************************************/
      
      if(commande == '1'){
        i1 = i1+5;
        servoBrasSecondaire.write(i1);
        //Serial.println("monter bras secondaire");
      }else if(commande == '2'){
        i1 = i1-5;
        servoBrasSecondaire.write(i1);
        //Serial.println("descendre bras secondaire");
      }
      Serial.println("Bras Secondaire");
      Serial.println(servoBrasSecondaire.read());


      if(commande == '3'){
        i2 = i2+5;
        servoBrasPrincipal.write(i2);
        //Serial.println("monter bras principal");
      }else if(commande == '4'){
        i2 = i2-5;
        servoBrasPrincipal.write(i2);
        //Serial.println("descendre bras principal");
      }
      Serial.println("Bras Principal");
      Serial.println(servoBrasPrincipal.read());
  }

char commande;

void setup() { 
   Serial.begin(9600);
   
   servoPince.attach(3); // pince
   servoRotationPince.attach(4); // rotation de la pince
   servoInclinaisonPince.attach(5); // inclinaison de la pince
   servoRotationBras.attach(8);
   servoTourneBras.attach(9);
   servoBrasSecondaire.attach(13);
   servoBrasPrincipal.attach(12);  // attache le servo au pin spécifié
   
   servoPince.write(p);
   servoRotationPince.write(rp);
   servoInclinaisonPince.write(i);
   servoRotationBras.write(rb);
   servoTourneBras.write(t);
   servoBrasSecondaire.write(i1);
   servoBrasPrincipal.write(i2);

  Serial.println("Attente réception !");
  Serial.flush();
  delay(2000);
  Serial.println("debut");
}

void loop() {
  if (Serial.available() != 0){
    /*Serial.println("");*/
  //else {
    Serial.print("actuellement : ");
    Serial.println(Serial.available());
    commande = Serial.read();
    ordre(commande);
  }
}
