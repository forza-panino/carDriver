#ifndef CARADAPTER_H
#define CARADAPTER_H
#include <map>
#include "settings.h"

//defining inside constants for mapping
#define ACCELERATION_R 81
#define ACCELERATION_L 80
#define STEERING_R 91
#define STEERING_L 90

class carAdapter {
  
  //declaring variables
  private: 
    //mapping 
    //act_char-> pin
    std::map<uint8_t, uint8_t> action_pin;

    //act_char -> status
    std::map<uint8_t, bool> action_status = {
      {ACCELERATION_R, false},
      {ACCELERATION_L, false},
      {STEERING_R, false},
      {STEERING_L, false}
    };
    
  public:
  
    //CONSTRUCTOR
    carAdapter(uint8_t acc_r_pin, uint8_t acc_l_pin, uint8_t steer_r_pin, uint8_t steer_l_pin);

  //private methods
  private:
  
    //COMMANDS ALREADY CHECKED -> EXECUTE
    //NOTE: same command will switch status: if A->0 and you send A then A->1, but sending again A will result in A->0 (stopping accelerating)
    void executeCarAction(uint8_t com_id);

  //public method to communicate
  public:

    //STOP ALL
    void stopCar();

    //ADAPT COM
    void adaptCarCom(char instruction[]);

};

#endif
