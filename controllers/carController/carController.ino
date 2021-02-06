#include "BTS7960.h"
#include "settings.h"

//DEFINING MOTOR CONTROLLERS
BTS7960 FL(L_EN_FL, R_EN_FL, L_PWM_FL, R_PWM_FL);
BTS7960 FR(L_EN_FR, R_EN_FR, L_PWM_FR, R_PWM_FR);
BTS7960 RL(L_EN_RL, R_EN_RL, L_PWM_RL, R_PWM_RL);
BTS7960 RR(L_EN_RR, R_EN_RR, L_PWM_RR, R_PWM_RR);



void setup() {

  analogReference(EXTERNAL);

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  pinMode(VEL1, INPUT);
  pinMode(VEL2, INPUT);
  pinMode(VEL3, INPUT);

  pinMode(ACCELERATE_R, INPUT);
  pinMode(ACCELERATE_L, INPUT);
  pinMode(STEER_R, INPUT);
  pinMode(STEER_L, INPUT);

  FL.Enable();
  FR.Enable();
  RL.Enable();
  RR.Enable();

  Serial.begin(115200);
  
}

void loop() {

  if (analogRead(VEL1) > 800) {
    Serial.write("VEL1 \n");
  }
  if (analogRead(VEL2) > 800) {
    Serial.write("VEL2 \n");
  }
  if (analogRead(VEL3) > 800) {
    Serial.write("VEL3 \n");
  }
  
  if (analogRead(ACCELERATE_R) > 800) {
    Serial.write("ACCELERATE_R \n");
    digitalWrite(LED_BUILTIN, HIGH);
  }
  if (analogRead(ACCELERATE_L) > 800) {
    Serial.write("ACCELERATE_L \n");
    digitalWrite(LED_BUILTIN, HIGH);
  }
  if (analogRead(STEER_R) > 800) {
    Serial.write("STEER_R \n");
    digitalWrite(LED_BUILTIN, HIGH);
  }
  if (analogRead(STEER_L) > 800) {
    Serial.write("STEER_L \n");
    digitalWrite(LED_BUILTIN, HIGH);
  }

  Serial.write("------------------\n");
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  
}
