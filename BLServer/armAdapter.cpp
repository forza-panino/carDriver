#include "Arduino.h"
#include <map>
#include "settings.h"
#include "armAdapter.h"

armAdapter::armAdapter(uint8_t arm_rot_pin, uint8_t tilt_pin, uint8_t claw_pin, uint8_t lift_pin, uint8_t pos_dir_pin, uint8_t neg_pos_pin) {
  //action pin mapping
  action_pin.insert(std::pair<char, uint8_t>(ARM_ROTATION, arm_rot_pin));
  action_pin.insert(std::pair<char, uint8_t>(TILTING, tilt_pin));
  action_pin.insert(std::pair<char, uint8_t>(CLAW_ACT, claw_pin));
  action_pin.insert(std::pair<char, uint8_t>(LIFT, lift_pin));
  action_pin.insert(std::pair<char, uint8_t>(POSITIVE_DIR, pos_dir_pin));
  action_pin.insert(std::pair<char, uint8_t>(NEGATIVE_DIR, neg_pos_pin));

  //setting pins on LOW
  for (std::map<char, uint8_t>::iterator pos = action_pin.begin(); pos != action_pin.end(); pos++) {
    digitalWrite(pos->second, LOW);
  }  
}


void armAdapter::stopArm() {
  //first stop actions
  digitalWrite(action_pin.find(ARM_ROTATION)->second, LOW);
  digitalWrite(action_pin.find(TILTING)->second, LOW);
  digitalWrite(action_pin.find(CLAW_ACT)->second, LOW);
  digitalWrite(action_pin.find(LIFT)->second, LOW);
  //now dirs
  digitalWrite(action_pin.find(POSITIVE_DIR)->second, LOW);
  digitalWrite(action_pin.find(NEGATIVE_DIR)->second, LOW);
  //update status
  for (std::map<char, bool>::iterator pos = action_status.begin(); pos != action_status.end(); pos++) {
    pos->second = false;
  }
}

void armAdapter::executeArmAction(char com_id) {
  
  std::map<char, bool>::iterator iter = action_status.find(com_id);
  bool value = iter->second;
  
  switch (com_id) {
    
    case ARM_ROTATION:
      digitalWrite(action_pin.find(ARM_ROTATION)->second, !value );
      iter->second = !value;
      break;
    
    case TILTING:
      digitalWrite(action_pin.find(TILTING)->second, !value);
      iter->second = !value;
      break;

    case CLAW_ACT:
      digitalWrite(action_pin.find(CLAW_ACT)->second, !value );
      iter->second = !value;
      break;
    
    case LIFT:
      digitalWrite(action_pin.find(LIFT)->second, !value);
      iter->second = !value;
      break;

    case POSITIVE_DIR:
      if (action_status.find(NEGATIVE_DIR)->second == false) { //preventing contrasting directions
        digitalWrite(action_pin.find(POSITIVE_DIR)->second, !value);
        iter->second = !value;
      }
      break;

    case NEGATIVE_DIR:
      if (action_status.find(POSITIVE_DIR)->second == false) { //preventing contrasting directions
        digitalWrite(action_pin.find(NEGATIVE_DIR)->second, !value);
        iter->second = !value;
      }
      break;
      
  }
}


void armAdapter::adaptArmCom(char instruction) {

  if ( ( (instruction == ARM_ROTATION) or (instruction == TILTING) ) or (instruction == CLAW_ACT) or (instruction == LIFT) or (instruction == POSITIVE_DIR) or (instruction == NEGATIVE_DIR)) {
    executeArmAction(instruction);
  }
  
}
