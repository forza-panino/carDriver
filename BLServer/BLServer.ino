#include "BluetoothSerial.h"
#include "commsHandler.h"
#include "settings.h"

//declaring variables for message elaboration
BluetoothSerial SerialBT;
char HANDSHAKE[9] = {'h', 'a', 'n', 'd', 's', 'h', 'a', 'k', 'e'};
char DISC[4] = {'D', 'I', 'S', 'C'} ;
bool handshake_complete = false;
char inbound;
char command[9];
uint8_t msgpos = 0;

commsHandler comms_handler(CAR, VEL2);

void setup() {
  
  pinMode(ACCELERATION_R_PIN, OUTPUT);
  pinMode(ACCELERATION_L_PIN, OUTPUT);
  pinMode(STEERING_R_PIN, OUTPUT);
  pinMode(STEERING_L_PIN, OUTPUT);
  pinMode(CAR_VEL1_PIN, OUTPUT);
  pinMode(CAR_VEL2_PIN, OUTPUT);
  pinMode(CAR_VEL3_PIN, OUTPUT);

  pinMode(ARM_ROTATION_R_PIN, OUTPUT);
  pinMode(ARM_ROTATION_L_PIN, OUTPUT);
  pinMode(TILTING_R_PIN, OUTPUT);
  pinMode(TILTING_L_PIN, OUTPUT);
  pinMode(CLAW_ACT_R_PIN, OUTPUT);
  pinMode(CLAW_ACT_L_PIN, OUTPUT);
  pinMode(LIFT_R_PIN, OUTPUT);
  pinMode(LIFT_L_PIN, OUTPUT);
  pinMode(ARM_VEL1_PIN, OUTPUT);
  pinMode(ARM_VEL2_PIN, OUTPUT);
  pinMode(ARM_VEL3_PIN, OUTPUT);
  
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
          comms_handler.handleComm(command);
        }
        
      }
      msgpos = 0; //restart message builder
      std::fill(command, command+9, ' '); //cleaning command
    }
    
  }
}
