#include <Servo.h>
#include "settings.h"

Servo claw_servo;
Servo lift_servo;
Servo tilt_servo;
Servo rotation_servo;

uint8_t claw_position = INITIAL_POSITION;
uint8_t tilt_position = INITIAL_POSITION;
uint8_t rotation_position = INITIAL_POSITION;
uint8_t lift_position = INITIAL_POSITION;

void claw(uint8_t i) { //1 or -1
  if ((i-1) >= 45 or (i+1) <= 120){
    claw_position += i;
    claw_servo.write(claw_position);
  }
}

void tilt(uint8_t i) { //1 or -1
  if ((i-1) >= 25 or (i+1) <= 180){
    tilt_position += i;
    tilt_servo.write(tilt_position);
  }
}

void rotate(uint8_t i) { //1 or -1
  if ((i-1) >= 1 or (i+1) <= 180){
    rotation_position += i;
    rotation_servo.write(rotation_position);
  }
}

void lift(uint8_t i) { //1 or -1
  if ((i-1) >= 1 or (i+1) <= 135){
    lift_position += i;
    lift_servo.write(lift_position);
  }
}


void setup() {

  pinMode(VEL1_PIN, INPUT);
  pinMode(VEL2_PIN, INPUT);
  pinMode(LIFT_R_INP_PIN, INPUT);
  pinMode(LIFT_L_INP_PIN, INPUT);
  pinMode(TILTING_R_PIN, INPUT);
  pinMode(TILTING_R_PIN, INPUT);
  pinMode(CLAW_R_PIN, INPUT);
  pinMode(CLAW_L_PIN, INPUT);
  pinMode(ROTATE_R_PIN, INPUT);
  pinMode(ROTATE_L_PIN, INPUT);

  claw_servo.attach(CLAW_SERVO_PIN);
  lift_servo.attach(LIFT_SERVO_PIN);
  tilt_servo.attach(TILT_SERVO_PIN);
  rotation_servo.attach(ROTATE_SERVO_PIN);

  claw_servo.write(INITIAL_POSITION);
  lift_servo.write(INITIAL_POSITION);
  tilt_servo.write(INITIAL_POSITION);
  rotation_servo.write(INITIAL_POSITION);
  
}
void loop(){

  if (digitalRead(LIFT_R_INP_PIN)) {
    lift(1);
  }
  if (digitalRead(LIFT_L_INP_PIN)) {
    lift(-1);
  }
  if (digitalRead(TILTING_R_PIN)) {
    tilt(1);
  }
  if (digitalRead(TILTING_L_PIN)) {
    tilt(-1);
  }
  if (digitalRead(CLAW_R_PIN)) {
    claw(1);
  }
  if (digitalRead(CLAW_L_PIN)) {
    claw(-1);
  }
  if (digitalRead(ROTATE_R_PIN)) {
    rotate(1);
  }
  if (digitalRead(ROTATE_L_PIN)) {
    rotate(-1);
  }

  delay(digitalRead(VEL1_PIN) ? 17 : 7);
  
}
