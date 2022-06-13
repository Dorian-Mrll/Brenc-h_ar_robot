#include "arduino_final.h"



servomoteur begin(Servo & obj, uint8_t angle, uint8_t pin, uint8_t min, uint8_t max) {

  servomoteur res_servo = {obj, 0, angle, pin, min, max};

  res_servo.servo.attach(res_servo.pin); // attache le servo au pin spécifié
  res_servo.servo.write(res_servo.angle);

  return res_servo;
}


void reset(struct servomoteur * servo, uint8_t angle) {

  servo->angle = angle;
  servo->servo.write(servo->angle);
  servo->etat = 0;
}





// permet de changer la position du servomoteur
void move(struct servomoteur * servo) {

  //delay(80);
  if (servo->etat == 1 && servo->servo.read() < servo->max) {
    if (servo->servo.read() > servo->max - 10) delay(80);
    servo->angle = servo->angle + 4;
  }
  else if (servo->etat == -1 && servo->servo.read() > servo->min) {
    if (servo->servo.read() < servo->min + 10) delay(80);
    servo->angle = servo->angle - 4;
  }
  servo->servo.write(servo->angle);
}
