#ifndef ARDUINO_FINAL_H
#define ARDUINO_FINAL_H

#include <Arduino.h>
#include <Servo.h>

// associe les variables utilisé au numéro de PIN sur la carte arduino
#define PIN_PINCE 13
#define PIN_ROTATION_PINCE 12
#define PIN_INCLINAISON_PINCE 11
#define PIN_ROTATION_BRAS 9
#define PIN_TOURNE_BRAS 8
#define PIN_AVANT_BRAS 6
#define PIN_BRAS 5


// Structure permettant de définir les servomoteurs
typedef struct servomoteur {
    Servo servo;              // objet servomoteur associé (utilisé pour lire et ecrire sur le servomoteur) fonctions servo.read() et servo.write(valeur)
    int etat;                 // etat du servomoteur 1:incrémente, 0:ne bouge pas, -1:décrémente (0 de base)
    int angle;                // angle actuel du servomoteur
    int pin;                  // numéro de PIN associé au servomoteur
    uint8_t min;                  // valeur minimale que peut atteindre le servomoteur
    uint8_t max;                  // valeur maximale que peut atteindre le servomoteur
}
servomoteur;


// fonctions créés pour simplifier le code

// fonction servomoteur qui prend en argment un objet Servo, un angle de départ et le numéro de pin assosié sa valeur minimal possible et sa valeur maxiamale à ne pas dépasser
// et qui instancie un object de type servomoteur
servomoteur begin(Servo & obj, uint8_t angle, uint8_t pin, uint8_t min, uint8_t max);

// fonction qui va réinitialiser l'angle du servomoteur entré en paramètre
void reset(struct servomoteur * servo, uint8_t angle);

// fonction qui va renvoyer à l'ESP32 les valurs des dégrés des angles actuels
void data_servomotor();

// fonction qui va modifier l'état d'un servomoteur en fonction de la commande récupérer
void order(String commande);

// fonction qui va écouter sur le lien de communnication le buffer et stocker un a un les caractères reçu jusqu'au caractère de fin de chaine qui va renvoyer le String à la fonction order
void receive();

// fonction qui permet d'incrementer ou de decrémenter l'angle de chaque servomoteur en fonction de l'état du servomoteur
void move(struct servomoteur * servo);

#endif
