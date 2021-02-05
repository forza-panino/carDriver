#include "Arduino.h"
#include "settings.h"
#include "carAdapter.h"
#include "armAdapter.h"
#include "commsHandler.h"

commsHandler::commsHandler(char machine, uint8_t velocity) {
  this->machine = machine;
  changeVelocity(velocity);
  car_adapter = new carAdapter(ACCELERATION_PIN, STEERING_PIN, POSITIVE_DIR_CAR_PIN, NEGATIVE_DIR_CAR_PIN);
  arm_adapter = new armAdapter(ARM_ROTATION_PIN, TILTING_PIN, CLAW_ACT_PIN, LIFT_PIN, POSITIVE_DIR_ARM_PIN, NEGATIVE_DIR_ARM_PIN);
}

void commsHandler::switchMachine() {
  
  if (machine == CAR) {
    
    //stopping car
    car_adapter->stopCar();
    //turning off CAR_VEL pins (I think that for performances it is better to put everything on low instead of searching for the one HIGH)
    digitalWrite(CAR_VEL1_PIN, LOW);
    digitalWrite(CAR_VEL2_PIN, LOW);
    digitalWrite(CAR_VEL3_PIN, LOW);

    machine = ARM; //changing machine in use

    switch (velocity) { //passing previous vel setting to actual machine

      case VEL1:
        digitalWrite(ARM_VEL1_PIN, HIGH);
        break;

      case VEL2:
        digitalWrite(ARM_VEL2_PIN, HIGH);
        break;

      case VEL3:
        digitalWrite(ARM_VEL3_PIN, HIGH);
        break;
      
    }
    
  }

  else { //same operations but on other machine
    
    arm_adapter->stopArm();
    digitalWrite(ARM_VEL1_PIN, LOW);
    digitalWrite(ARM_VEL2_PIN, LOW);
    digitalWrite(ARM_VEL3_PIN, LOW);

    machine = CAR;

    switch (velocity) {

      case VEL1:
        digitalWrite(CAR_VEL1_PIN, HIGH);
        break;

      case VEL2:
        digitalWrite(CAR_VEL2_PIN, HIGH);
        break;

      case VEL3:
        digitalWrite(CAR_VEL3_PIN, HIGH);
        break;

    }
    
  }
  
}




void commsHandler::changeVelocity(char velocity){

  switch (velocity) {

    case VEL1:

      if (machine == CAR) {
        digitalWrite(CAR_VEL2_PIN, LOW);
        digitalWrite(CAR_VEL3_PIN, LOW);
        digitalWrite(CAR_VEL1_PIN, HIGH);
        break;
      }
      else {
        digitalWrite(ARM_VEL2_PIN, LOW);
        digitalWrite(ARM_VEL3_PIN, LOW);
        digitalWrite(ARM_VEL1_PIN, HIGH);
        break;
      }

    case VEL2:

      if (machine == CAR) {
        digitalWrite(CAR_VEL1_PIN, LOW);
        digitalWrite(CAR_VEL3_PIN, LOW);
        digitalWrite(CAR_VEL2_PIN, HIGH);
        break;
      }
      else {
        digitalWrite(ARM_VEL1_PIN, LOW);
        digitalWrite(ARM_VEL3_PIN, LOW);
        digitalWrite(ARM_VEL2_PIN, HIGH);
        break;
      }

    case VEL3:

      if (machine == CAR) {
        digitalWrite(CAR_VEL1_PIN, LOW);
        digitalWrite(CAR_VEL2_PIN, LOW);
        digitalWrite(CAR_VEL3_PIN, HIGH);
        break;
      }
      else {
        digitalWrite(ARM_VEL1_PIN, LOW);
        digitalWrite(ARM_VEL2_PIN, LOW);
        digitalWrite(ARM_VEL3_PIN, HIGH);
        break;
      }
   
  }

  this->velocity = velocity;

}



void commsHandler::sendToAdapter(char command) {

  if (machine == CAR){car_adapter->adaptCarCom(command);}
  else {arm_adapter->adaptArmCom(command);}
 
}

void commsHandler::handleComm(char command[]) {
  switch (command[0]) {

    case SELECT_MACHINE:
      switchMachine();
      break;

    case SELECT_VELOCITY:
      changeVelocity(command[1]);
      break;

    default:
      sendToAdapter(command[0]);
      break;
      
  }
  
}
