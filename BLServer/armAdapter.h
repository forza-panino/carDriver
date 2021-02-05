#ifndef ARMADAPTER_H
#define ARMADAPTER_H
#include <map>
#include "settings.h"

class armAdapter {
  
  //declaring variables
  private: 
    //mapping 
    //act_char-> pin
    std::map<char, uint8_t> action_pin;

    //act_char -> status
    std::map<char, bool> action_status = {
      {ARM_ROTATION, false},
      {TILTING, false},
      {CLAW_ACT, false},
      {LIFT, false},
      {POSITIVE_DIR, false},
      {NEGATIVE_DIR, false}
    };

  public:
  
    //CONSTRUCTOR
    armAdapter(uint8_t arm_rot_pin, uint8_t tilt_pin, uint8_t claw_pin, uint8_t lift_pin, uint8_t pos_dir_pin, uint8_t neg_pos_pin);


  //private methods
  private:

  //COMMANDS ALREADY CHECKED -> EXECUTE
  //NOTE: same command will switch status: if R->0 and you send R then R->1, but sending again R will result in R->0 (stopping accelerating)
  void executeArmAction(char com_id);

  //public methods
  public:
  
    //STOP ALL
    void stopArm();
    
    //ADAPT COM
    void adaptArmCom(char instruction);

};

#endif
