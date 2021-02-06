#include "Arduino.h"
#include <map>
#include "settings.h"
#include "armAdapter.h"

armAdapter::armAdapter(uint8_t arm_rot_r_pin, uint8_t arm_rot_l_pin, uint8_t tilt_r_pin, uint8_t tilt_l_pin, uint8_t claw_r_pin,  uint8_t claw_l_pin, uint8_t lift_r_pin, uint8_t lift_l_pin) {
  //action pin mapping
  action_pin.insert(std::pair<uint8_t, uint8_t>(ARM_ROTATION_R, arm_rot_r_pin));
  action_pin.insert(std::pair<uint8_t, uint8_t>(ARM_ROTATION_L, arm_rot_l_pin));
  action_pin.insert(std::pair<uint8_t, uint8_t>(TILTING_R, tilt_r_pin));
  action_pin.insert(std::pair<uint8_t, uint8_t>(TILTING_L, tilt_l_pin));
  action_pin.insert(std::pair<uint8_t, uint8_t>(CLAW_ACT_R, claw_r_pin));
  action_pin.insert(std::pair<uint8_t, uint8_t>(CLAW_ACT_L, claw_l_pin));
  action_pin.insert(std::pair<uint8_t, uint8_t>(LIFT_R, lift_r_pin));
  action_pin.insert(std::pair<uint8_t, uint8_t>(LIFT_L, lift_l_pin));

  //setting pins on LOW
  for (std::map<uint8_t, uint8_t>::iterator pos = action_pin.begin(); pos != action_pin.end(); pos++) {
    digitalWrite(pos->second, LOW);
  }  
}


void armAdapter::stopArm() {
  digitalWrite(action_pin.find(ARM_ROTATION_R)->second, LOW);
  digitalWrite(action_pin.find(ARM_ROTATION_L)->second, LOW);
  digitalWrite(action_pin.find(TILTING_R)->second, LOW);
  digitalWrite(action_pin.find(TILTING_L)->second, LOW);
  digitalWrite(action_pin.find(CLAW_ACT_R)->second, LOW);
  digitalWrite(action_pin.find(CLAW_ACT_L)->second, LOW);
  digitalWrite(action_pin.find(LIFT_R)->second, LOW);
  digitalWrite(action_pin.find(LIFT_L)->second, LOW);
  //update status
  for (std::map<uint8_t, bool>::iterator pos = action_status.begin(); pos != action_status.end(); pos++) {
    pos->second = false;
  }
}

void armAdapter::executeArmAction(uint8_t com_id) {
  
  std::map<uint8_t, bool>::iterator iter = action_status.find(com_id);
  bool value = iter->second;
  
  switch (com_id) {
    
    case ARM_ROTATION_R:
      if (action_status.find(ARM_ROTATION_L)->second == false) { //preventing contrasting directions
        digitalWrite(action_pin.find(ARM_ROTATION_R)->second, !value );
        iter->second = !value; //updating status
      }
      break;
    
    case ARM_ROTATION_L:
      if (action_status.find(ARM_ROTATION_R)->second == false) { //preventing contrasting directions
        digitalWrite(action_pin.find(ARM_ROTATION_L)->second, !value);
        iter->second = !value; //updating status
      }
      break;

    case TILTING_R:
      if (action_status.find(TILTING_L)->second == false) { //preventing contrasting directions
        digitalWrite(action_pin.find(TILTING_R)->second, !value );
        iter->second = !value; //updating status
      }
      break;
    
    case TILTING_L:
      if (action_status.find(TILTING_R)->second == false) { //preventing contrasting directions
        digitalWrite(action_pin.find(TILTING_L)->second, !value );
        iter->second = !value; //updating status
      }
      break;

    case CLAW_ACT_R:
      if (action_status.find(CLAW_ACT_L)->second == false) { //preventing contrasting directions
        digitalWrite(action_pin.find(CLAW_ACT_R)->second, !value);
        iter->second = !value; //updating status
      }
      break;

    case CLAW_ACT_L:
      if (action_status.find(CLAW_ACT_R)->second == false) { //preventing contrasting directions
        digitalWrite(action_pin.find(CLAW_ACT_L)->second, !value);
        iter->second = !value; //updating status
      }
      break;

    case LIFT_R:
      if (action_status.find(LIFT_L)->second == false) { //preventing contrasting directions
        digitalWrite(action_pin.find(LIFT_R)->second, !value);
        iter->second = !value;
      }
      break;

    case LIFT_L:
      if (action_status.find(LIFT_R)->second == false) { //preventing contrasting directions
        digitalWrite(action_pin.find(LIFT_L)->second, !value);
        iter->second = !value;
      }
      break;
      
  }
}


void armAdapter::adaptArmCom(char instruction[]) {

  switch (instruction[0]) {

    case ARM_ROTATION:

      switch (instruction[1]) {
        
        case POSITIVE_DIR:
          executeArmAction(ARM_ROTATION_R);
          break;
        case NEGATIVE_DIR:
          executeArmAction(ARM_ROTATION_L);
          break;
          
      }

      break;


   case TILTING:

      switch (instruction[1]) {
        
        case POSITIVE_DIR:
          executeArmAction(TILTING_R);
          break;
        case NEGATIVE_DIR:
          executeArmAction(TILTING_L);
          break;
          
      }

      break;


   case CLAW_ACT:

      switch (instruction[1]) {
        
        case POSITIVE_DIR:
          executeArmAction(CLAW_ACT_R);
          break;
        case NEGATIVE_DIR:
          executeArmAction(CLAW_ACT_L);
          break;
          
      }

      break;


   case LIFT:

      switch (instruction[1]) {
        
        case POSITIVE_DIR:
          executeArmAction(LIFT_R);
          break;
        case NEGATIVE_DIR:
          executeArmAction(LIFT_L);
          break;
          
      }

      break;


  }
  
}
