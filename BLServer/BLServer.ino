#include "BluetoothSerial.h"
#include "carAdapter.cpp"

//END OF COMMS
#define EOC '\n'

//COMMANDS CONSTANTS
#define SETTING_VELOCITY 'V'
#define ARM_ROTATION 'R'
#define TILTING 'T'
#define CLAW_ACT 'C'
#define LIFT 'L'

//DEFINING OUTPUT PINS
//action pins
#define ACCELERATE 26
#define STEER 27
//dir pins
#define POSITIVE_DIR_PIN 23
#define NEGATIVE_DIR_PIN 22
//vel pins
#define VEL1 32
#define VEL2 33
#define VEL3 25

//declaring variables for message elaboration
BluetoothSerial SerialBT;
char HANDSHAKE[9] = {'h', 'a', 'n', 'd', 's', 'h', 'a', 'k', 'e'};
char DISC[4] = {'D', 'I', 'S', 'C'} ;
bool handshake_complete = false;
char inbound;
char command[9];
int msgpos = 0;

carAdapter car_adapter(ACCELERATE, STEER, POSITIVE_DIR_PIN, NEGATIVE_DIR_PIN);


void setup() {
  
  pinMode(ACCELERATE, OUTPUT);
  pinMode(STEER, OUTPUT);
  pinMode(POSITIVE_DIR_PIN, OUTPUT);
  pinMode(NEGATIVE_DIR_PIN, OUTPUT);
  pinMode(VEL1, OUTPUT);
  pinMode(VEL2, OUTPUT);
  pinMode(VEL3, OUTPUT);
  
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
        for (int i = 0; i < 9; i++) { if (command[i] != HANDSHAKE[i]) { handshake_complete = false; break; } } //check handhsake
        if (handshake_complete) { SerialBT.println("handshake\n"); Serial.write("handshake complete");}
        else { SerialBT.print("invalid handshake\n"); Serial.write("invalid handshake"); }
      }

      else { //handshake complete, now ready to receive commands
        bool disc = (msgpos == 0) ? false : true; //checking zero-length message
        for (int i = 0; i < 4; i++) { if (command[i] != DISC[i]) { disc = false; break; } } //checking if disconnected
        if (disc) {handshake_complete = false; Serial.write("Disconnected"); } //device disconnected
        
        else { //INBOUND COMMAND TO ELABORATE
          car_adapter.handleCarCom(command[0]);
        }
        
      }
      msgpos = 0; //restart message builder
    }
    
  }
}
