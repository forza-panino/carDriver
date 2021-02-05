#include <map>
#include "Arduino.h"
#include "settings.h"
#include "carAdapter.h"

carAdapter::carAdapter(uint8_t acc_pin, uint8_t steer_pin, uint8_t pos_dir_pin, uint8_t neg_pos_pin) {
      
  //action pin mapping
  action_pin.insert(std::pair<char, uint8_t>(ACCELERATION, acc_pin));
  action_pin.insert(std::pair<char, uint8_t>(STEERING, steer_pin));
  action_pin.insert(std::pair<char, uint8_t>(POSITIVE_DIR, pos_dir_pin));
  action_pin.insert(std::pair<char, uint8_t>(NEGATIVE_DIR, neg_pos_pin));

  //setting pins on LOW
  for (std::map<char, uint8_t>::iterator pos = action_pin.begin(); pos != action_pin.end(); pos++) {
    digitalWrite(pos->second, LOW);
  }
  
}



void carAdapter::stopCar() {
  //first stop actions
  digitalWrite(action_pin.find(ACCELERATION)->second, LOW);
  digitalWrite(action_pin.find(STEERING)->second, LOW);
  //now dirs
  digitalWrite(action_pin.find(POSITIVE_DIR)->second, LOW);
  digitalWrite(action_pin.find(NEGATIVE_DIR)->second, LOW);
  //update status
  for (std::map<char, bool>::iterator pos = action_status.begin(); pos != action_status.end(); pos++) {
    pos->second = false;
  }
}



void carAdapter::executeCarAction(char com_id) {
        
  std::map<char, bool>::iterator iter = action_status.find(com_id);
  bool value = iter->second;
  
  switch (com_id) {
    
    case ACCELERATION:
      digitalWrite(action_pin.find(ACCELERATION)->second, !value );
      iter->second = !value;
      break;
    
    case STEERING:
      digitalWrite(action_pin.find(STEERING)->second, !value);
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



void carAdapter::adaptCarCom(char instruction) {

  if ( ( (instruction == ACCELERATION) or (instruction == STEERING) ) or (instruction == POSITIVE_DIR) or (instruction == NEGATIVE_DIR) ) {
    executeCarAction(instruction);
  }
  
}
