#ifndef ARMADAPTER_H
#define ARMADAPTER_H
#include <map>
#include "settings.h"

//defining inside constants for mapping
#define ARM_ROTATION_R 41
#define ARM_ROTATION_L 40
#define TILTING_R 51
#define TILTING_L 50
#define LIFT_R 61
#define LIFT_L 60
#define CLAW_ACT_R 71
#define CLAW_ACT_L 70


class armAdapter {
  
  //declaring variables
  private: 
    //mapping 
    //act_char-> pin
    std::map<uint8_t, uint8_t> action_pin;

    //act_char -> status
    std::map<uint8_t, bool> action_status = {
      {ARM_ROTATION_R, false},
      {ARM_ROTATION_L, false},
      {TILTING_R, false},
      {TILTING_L, false},
      {LIFT_R, false},
      {LIFT_L, false},
      {CLAW_ACT_R, false},
      {CLAW_ACT_L, false}
    };

  public:
  
    //CONSTRUCTOR
    armAdapter(uint8_t arm_rot_r_pin, uint8_t arm_rot_l_pin, uint8_t tilt_r_pin, uint8_t tilt_l_pin, uint8_t claw_r_pin,  uint8_t claw_l_pin, uint8_t lift_r_pin, uint8_t lift_l_pin);


  //private methods
  private:

  //COMMANDS ALREADY CHECKED -> EXECUTE
  //NOTE: same command will switch status: if R->0 and you send R then R->1, but sending again R will result in R->0 (stopping accelerating)
  void executeArmAction(uint8_t com_id);

  //public methods
  public:
  
    //STOP ALL
    void stopArm();
    
    //ADAPT COM
    void adaptArmCom(char instruction[]);

};

#endif
