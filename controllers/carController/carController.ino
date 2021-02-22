#include "BTS7960.h"
#include "settings.h"

//DEFINING MOTOR CONTROLLERS
BTS7960 FL(L_EN_FL, R_EN_FL, L_PWM_FL, R_PWM_FL);
BTS7960 FR(L_EN_FR, R_EN_FR, L_PWM_FR, R_PWM_FR);
BTS7960 RL(L_EN_RL, R_EN_RL, L_PWM_RL, R_PWM_RL);
BTS7960 RR(L_EN_RR, R_EN_RR, L_PWM_RR, R_PWM_RR);

//defining velocity variable
uint8_t velocity = 130;

//actions status
bool isAcc_R = false;
bool isAcc_L = false;

bool shouldStop = true;



void setup() {

  analogReference(EXTERNAL);

  pinMode(VEL1_PIN, INPUT);
  pinMode(VEL2_PIN, INPUT);
  pinMode(VEL3_PIN, INPUT);

  pinMode(ACCELERATE_R, INPUT);
  pinMode(ACCELERATE_L, INPUT);
  pinMode(STEER_R, INPUT);
  pinMode(STEER_L, INPUT);

  FL.Enable();
  FR.Enable();
  RL.Enable();
  RR.Enable();
  
}

void loop() {

  if (digitalRead(VEL1_PIN)) {
    velocity = VEL1;
  }
  if (digitalRead(VEL2_PIN)) {
    velocity = VEL2;
  }
  if (digitalRead(VEL3_PIN)) {
    velocity = VEL3;
  }
  
  if (digitalRead(ACCELERATE_R)) {
    RR.TurnRight(velocity);
    RL.TurnRight(velocity);
    FR.TurnRight(velocity);
    FL.TurnRight(velocity);
    isAcc_R = true;
    shouldStop = false;
  } else { isAcc_R = false; shouldStop = true;}
  
  if (digitalRead(ACCELERATE_L)) {
    RR.TurnLeft(velocity);
    RL.TurnLeft(velocity);
    FR.TurnLeft(velocity);
    FL.TurnLeft(velocity);
    isAcc_L = true;
    shouldStop = false;
  } else { isAcc_L = false; shouldStop = true;}
  
  if (digitalRead(STEER_R)) {
    if (!isAcc_R and !isAcc_L) { //steering on the spot
      FL.TurnRight(velocity);
      RR.TurnLeft(velocity);
      RL.TurnRight(velocity);
      FR.TurnLeft(velocity);
    }
    else { //steering while accelerating

      if (isAcc_R) {
        FL.TurnRight(VEL3);
        RR.TurnRight(VEL1);
        RL.TurnRight(VEL3);
        FR.TurnRight(VEL1);
      }
      else {
        FL.TurnLeft(VEL3);
        RR.TurnLeft(VEL1);
        RL.TurnLeft(VEL3);
        FR.TurnLeft(VEL1);
      }
      
    }
    shouldStop = false;
  } else {shouldStop = true;}
  
  if (digitalRead(STEER_L)) {
    if (!isAcc_R and !isAcc_L) { //steering on the spot
      FR.TurnRight(velocity);
      RL.TurnLeft(velocity);
      RR.TurnRight(velocity);
      FL.TurnLeft(velocity);
    }
    else { //steering while accelerating

      if (isAcc_R) {
        FR.TurnRight(VEL3);
        RL.TurnRight(VEL1);
        RR.TurnRight(VEL3);
        FL.TurnRight(VEL1);
      }
      else {
        FR.TurnLeft(VEL3);
        RL.TurnLeft(VEL1);
        RR.TurnLeft(VEL3);
        FL.TurnLeft(VEL1);
      }
      
    }
    shouldStop = false;
  } else {shouldStop = true;}

  if (shouldStop) { RR.Stop(); RL.Stop(); FR.Stop(); FL.Stop();  }
  
}

