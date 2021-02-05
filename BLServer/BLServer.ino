#include "BluetoothSerial.h"
/*#include "carAdapter.cpp"
#include "armAdapter.cpp"*/
#include "settingsHandler.cpp"

//END OF COMMS
#define EOC '\n'

//DEFINING OUTPUT PINS
//ACTION pins
//car pins
#define ACCELERATION_PIN 14
#define STEERING_PIN 12
//arm pins
#define ARM_ROTATION_PIN 13
#define TILTING_PIN 15
#define CLAW_ACT_PIN 16
#define LIFT_PIN 17
//DIRECTION pins
//car pins
#define POSITIVE_DIR_CAR_PIN 32
#define NEGATIVE_DIR_CAR_PIN 33
//arm pins
#define POSITIVE_DIR_ARM_PIN 23
#define NEGATIVE_DIR_ARM_PIN 22
//VELOCIY pins
//car vel pins
#define CAR_VEL1 25
#define CAR_VEL2 26
#define CAR_VEL3 27
//arm vel pins
#define ARM_VEL1 21
#define ARM_VEL2 19
#define ARM_VEL3 18

//declaring variables for message elaboration
BluetoothSerial SerialBT;
char HANDSHAKE[9] = {'h', 'a', 'n', 'd', 's', 'h', 'a', 'k', 'e'};
char DISC[4] = {'D', 'I', 'S', 'C'} ;
bool handshake_complete = false;
char inbound;
char command[9];
uint8_t msgpos = 0;

//instatiating handlers and adapters
carAdapter car_adapter(ACCELERATION_PIN, STEERING_PIN, POSITIVE_DIR_CAR_PIN, NEGATIVE_DIR_CAR_PIN);
armAdapter arm_adapter(ARM_ROTATION_PIN, TILTING_PIN, CLAW_ACT_PIN, LIFT_PIN, POSITIVE_DIR_ARM_PIN, NEGATIVE_DIR_ARM_PIN);


void setup() {
  
  pinMode(ACCELERATION_PIN, OUTPUT);
  pinMode(STEERING_PIN, OUTPUT);
  pinMode(POSITIVE_DIR_CAR_PIN, OUTPUT);
  pinMode(NEGATIVE_DIR_CAR_PIN, OUTPUT);
  pinMode(CAR_VEL1, OUTPUT);
  pinMode(CAR_VEL2, OUTPUT);
  pinMode(CAR_VEL3, OUTPUT);

  pinMode(ARM_ROTATION_PIN, OUTPUT);
  pinMode(TILTING_PIN, OUTPUT);
  pinMode(CLAW_ACT_PIN, OUTPUT);
  pinMode(LIFT_PIN, OUTPUT);
  pinMode(POSITIVE_DIR_ARM_PIN, OUTPUT);
  pinMode(NEGATIVE_DIR_ARM_PIN, OUTPUT);
  pinMode(ARM_VEL1, OUTPUT);
  pinMode(ARM_VEL2, OUTPUT);
  pinMode(ARM_VEL3, OUTPUT);
  
  Serial.begin(115200);
  SerialBT.begin("ESP32-COMMANDS-RECEIVER"); //Bluetooth device name
}

void loop() {

  if (SerialBT.available()) {

    inbound = SerialBT.read(); //read inbound char; MESSAGES MUST BE RECEIVED CHAR PER CHAR

    if (inbound != EOC and msgpos <= 9) { command[msgpos] = inbound; msgpos++; } //build inbound message

    else { //COMMS END -> elaborate message

      if (!handshake_complete) { //first comm -> establishing handshake
        handshake_complete = (msgpos == 0) ? false : true; //checking zero-length message
        for (uint8_t i = 0; i < 9; i++) { if (command[i] != HANDSHAKE[i]) { handshake_complete = false; break; } } //check handhsake
        if (handshake_complete) { SerialBT.println("handshake\n"); Serial.write("handshake complete");}
        else { SerialBT.print("invalid handshake\n"); Serial.write("invalid handshake"); }
      }

      else { //handshake complete, now ready to receive commands
        bool disc = (msgpos == 0) ? false : true; //checking zero-length message
        for (uint8_t i = 0; i < 4; i++) { if (command[i] != DISC[i]) { disc = false; break; } } //checking if disconnected
        if (disc) {handshake_complete = false; Serial.write("Disconnected"); } //device disconnected
        
        else { //INBOUND COMMAND TO ELABORATE
          car_adapter.handleCarCom(command[0]);
          arm_adapter.handleArmCom(command[0]);
        }
        
      }
      msgpos = 0; //restart message builder
      std::fill(command, command+9, ' '); //cleaning command
    }
    
  }
}
