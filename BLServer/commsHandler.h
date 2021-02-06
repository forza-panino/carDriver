#ifndef COMMSHANDLER_H
#define COMMSHANDLER_H
#include "settings.h"
#include "armAdapter.h"
#include "carAdapter.h"

class commsHandler {
  
  //declaring variables
  private:
    char machine;
    uint8_t velocity;
    carAdapter* car_adapter;
    armAdapter* arm_adapter;

  public:
  
    //CONSTRUCTOR
    commsHandler(char machine, uint8_t velocity);

  //private methods
  private:

    void switchMachine();
    void changeVelocity(char velocity);
    void sendToAdapter(char command[]);

  //public methods
  public:

    void handleComm(char command[]);
  
};


#endif
