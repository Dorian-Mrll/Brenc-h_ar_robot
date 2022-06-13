#include "arduino_finalV2.h"


// initilaiser données servomoteurs
servomoteur begin(Servo & obj, uint8_t angle, uint8_t pin, uint8_t min, uint8_t max) {

  servomoteur res_servo = {obj, 0, angle, pin, min, max};
  res_servo.servo.attach(res_servo.pin); // attache le servo au pin spécifié
  res_servo.servo.write(res_servo.angle);

  return res_servo;
}


// reinitialiser données servomoteurs
void reset(struct servomoteur * servo, uint8_t angle) {

  servo->angle = angle;
  servo->servo.write(servo->angle);
  servo->etat = 0;
}



// permet de changer la position du servomoteur
void move(struct servomoteur * servo, int vitesse) {

  if (servo->etat == 1 && servo->servo.read() < servo->max) {
    if (servo->servo.read() > servo->max - 5) delay(80);
    servo->angle = servo->angle + 1;
  }
  else if (servo->etat == -1 && servo->servo.read() > servo->min) {
    if (servo->servo.read() < servo->min + 5) delay(80);
    servo->angle = servo->angle - 1;
  }
  
  servo->servo.write(servo->angle);
}
