#include "Servo.h"

Servo servoBrasPrincipal, servoBrasSecondaire, servoTourneBras, servoRotationBras, servoInclinaisonPince, servoRotationPince, servoPince; // création de l'objet "servo"
int i1 = 60, i2 = 110, t = 100, rb = 80, i = 45, rp = 60, p = 20;

void ordre(char commande) {

  /***************************** Pince **************************************/

  if (commande == 'P' && servoPince.read() <= 80) {
    p = p + 5;
    servoPince.write(p); // demande au servo de se déplacer à cette position
    Serial.println("OUVRE pince");
  } else if (commande == 'p' && servoPince.read() >= 10) {
    p = p - 5;
    if (p < 20) delay(200);
    servoPince.write(p);
    Serial.println("FERMER pince");
  }
  //Serial.println(servoPince.read());


  /***************************** Rotation Pince **************************************/

  if (commande == 'R' && servoRotationPince.read() < 170) { //160 max 0 min
    rp = rp + 5;
    servoRotationPince.write(rp);
    Serial.println("rotation pince droite");
  } else if (commande == 'r' && servoRotationPince.read() > 10) {
    rp = rp - 5;
    servoRotationPince.write(rp);
    Serial.println("rotation pince gauche");
  }
  /*Serial.println("Rotation");
    Serial.println(servoRotationPince.read());*/


  /***************************** Inclinaison Pince **************************************/

  if (commande == 'I') { //180 max 0 min possède des problèmes
    i = i + 5;
    servoInclinaisonPince.write(i);
    Serial.println("incline pince avant");
  } else if (commande == 'i') {
    i = i - 5;
    servoInclinaisonPince.write(i);
    Serial.println("incline pince arrière");
  }
  /*Serial.println("Inclinaison");
    Serial.println(servoInclinaisonPince.read());*/


  /***************************** Rotation Bras **************************************/

  if (commande == 'Y' && servoRotationBras.read() < 170) { //35 170gauche
    rb = rb + 5;
    servoRotationBras.write(rb);
    Serial.println("rotation bras gauche");
  } else if (commande == 'y' && servoRotationBras.read() > 35) {
    rb = rb - 5;
    servoRotationBras.write(rb);
    Serial.println("rotation bras droite");
  }
  //Serial.println(commande);
  //Serial.println(servoRotationBras.read());



  /***************************** Tourne Bras **************************************/

  if (commande == 'T' && servoTourneBras.read() < 170) {
    t = t + 5;
    servoTourneBras.write(t);
    Serial.println("tourne bras gauche");
  } else if (commande == 't' && servoTourneBras.read() > 10) {
    t = t - 5;
    servoTourneBras.write(t);
    Serial.println("tourne bras droite");
  }
  //Serial.println(commande);
  //Serial.println(servoTourneBras.read());



  /***************************** Control Bras **************************************/

  if (commande == '1'/* && servoBrasSecondaire.read() < 80*/) {
    i1 = i1 + 1;
    servoBrasSecondaire.write(i1);
    //Serial.println("monter bras secondaire");
  } else if (commande == '2'/* && servoBrasSecondaire.read() > 40*/) {
    i1 = i1 - 1;
    servoBrasSecondaire.write(i1);
    //Serial.println("descendre bras secondaire");
  }
  Serial.println("Bras Secondaire");
  Serial.println(servoBrasSecondaire.read());


  if (commande == '3'/* && servoBrasPrincipal.read() < 180*/) {
    i2 = i2 +1;

    servoBrasPrincipal.write(i2);
    //Serial.println("monter bras principal");
  } else if (commande == '4' /*&& servoBrasPrincipal.read() > 90*/) {
    i2 = i2 - 1;
    servoBrasPrincipal.write(i2);
    //Serial.println("descendre bras principal");
  }
  Serial.println("Bras Principal");
  Serial.println(servoBrasPrincipal.read());
}

char commande;


void begin(Servo obj) {


  obj.attach(10);
  obj.write(20);
}
void setup() {
  Serial.begin(9600);

  servoPince.attach(13); // pince
  servoRotationPince.attach(12); // rotation de la pince
  servoInclinaisonPince.attach(11); // inclinaison de la pince
  servoRotationBras.attach(9);
  servoTourneBras.attach(8);
  servoBrasSecondaire.attach(6);
  servoBrasPrincipal.attach(5);  // attache le servo au pin spécifié

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
  if (Serial.available() != 0) {
    /*Serial.println("");*/
    //else {
    Serial.print("actuellement : ");
    Serial.println(Serial.available());
    commande = Serial.read();
    ordre(commande);
  }
}
