#include <map>
#include "Arduino.h"
#include "settings.h"
#include "carAdapter.h"

carAdapter::carAdapter(uint8_t acc_r_pin, uint8_t acc_l_pin, uint8_t steer_r_pin, uint8_t steer_l_pin) {
      
  //action pin mapping
  action_pin.insert(std::pair<uint8_t, uint8_t>(ACCELERATION_R, acc_r_pin));
  action_pin.insert(std::pair<uint8_t, uint8_t>(ACCELERATION_L, acc_l_pin));
  action_pin.insert(std::pair<uint8_t, uint8_t>(STEERING_R, steer_r_pin));
  action_pin.insert(std::pair<uint8_t, uint8_t>(STEERING_L, steer_l_pin));

  //setting pins on LOW
  for (std::map<uint8_t, uint8_t>::iterator pos = action_pin.begin(); pos != action_pin.end(); pos++) {
    digitalWrite(pos->second, LOW);
  }
  
}



void carAdapter::stopCar() {
  
  digitalWrite(action_pin.find(ACCELERATION_R)->second, LOW);
  digitalWrite(action_pin.find(ACCELERATION_L)->second, LOW);
  digitalWrite(action_pin.find(STEERING_R)->second, LOW);
  digitalWrite(action_pin.find(STEERING_L)->second, LOW);
  //update status
  for (std::map<uint8_t, bool>::iterator pos = action_status.begin(); pos != action_status.end(); pos++) {
    pos->second = false;
  }
}



void carAdapter::executeCarAction(uint8_t com_id) {
        
  std::map<uint8_t, bool>::iterator iter = action_status.find(com_id);
  bool value = iter->second;
  
  switch (com_id) {
    
    case ACCELERATION_R:
      if (action_status.find(ACCELERATION_L)->second == false) { //preventing contrasting directions
        digitalWrite(action_pin.find(ACCELERATION_R)->second, !value );
        iter->second = !value; //updating status
      }
      break;
    
    case ACCELERATION_L:
      if (action_status.find(ACCELERATION_R)->second == false) {
        digitalWrite(action_pin.find(ACCELERATION_L)->second, !value);
        iter->second = !value; //updating status
      }
      break;

    case STEERING_R:
      if (action_status.find(STEERING_L)->second == false) { //preventing contrasting directions
        digitalWrite(action_pin.find(STEERING_R)->second, !value);
        iter->second = !value; //updating status
      }
      break;

    case STEERING_L:
      if (action_status.find(STEERING_R)->second == false) { //preventing contrasting directions
        digitalWrite(action_pin.find(STEERING_L)->second, !value);
        iter->second = !value; //updating status
      }
      break;
      
  }
}



void carAdapter::adaptCarCom(char instruction[]) {

  switch (instruction[0]) {

    case ACCELERATION:
    
      switch (instruction[1]) {

        case POSITIVE_DIR:
          executeCarAction(ACCELERATION_R);
          break;
        case NEGATIVE_DIR:
          executeCarAction(ACCELERATION_L);
          break;
          
      }

      break;


   case STEERING:

     switch (instruction[1]) {
      
        case POSITIVE_DIR:
          executeCarAction(STEERING_R);
          break;
        case NEGATIVE_DIR:
          executeCarAction(STEERING_L);
          break;
          
     }

     break;

  }
  
}
