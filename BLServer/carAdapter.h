#ifndef CARADAPTER_H
#define CARADAPTER_H
#include <map>
#include "settings.h"

class carAdapter {
  
  //declaring variables
  private: 
    //mapping 
    //act_char-> pin
    std::map<char, uint8_t> action_pin;

    //act_char -> status
    std::map<char, bool> action_status = {
      {ACCELERATION, false},
      {STEERING, false},
      {POSITIVE_DIR, false},
      {NEGATIVE_DIR, false}
    };
    
  public:
  
    //CONSTRUCTOR
    carAdapter(uint8_t acc_pin, uint8_t steer_pin, uint8_t pos_dir_pin, uint8_t neg_pos_pin);

  //private methods
  private:
  
    //COMMANDS ALREADY CHECKED -> EXECUTE
    //NOTE: same command will switch status: if A->0 and you send A then A->1, but sending again A will result in A->0 (stopping accelerating)
    void executeCarAction(char com_id);

  //public method to communicate
  public:

    //STOP ALL
    void stopCar();

    //ADAPT COM
    void adaptCarCom(char instruction);

};

#endif
