#ifndef SETTINGS_H
#define SETTINGS_H

//END OF COMMS
#define EOC '\n'

//COMMANDS CONSTANTS
//arm
#define ARM_ROTATION 'P'
#define TILTING 'B'
#define CLAW_ACT 'G'
#define LIFT 'W'
//car
#define STEERING 'S'
#define ACCELERATION 'T'
//machine selectors
#define CAR 'C'
#define ARM 'A'
//velocity selectors
#define VEL1 '1'
#define VEL2 '2'
#define VEL3 '3'
//machine select command
#define SELECT_MACHINE 'M'
//velocity select command
#define SELECT_VELOCITY 'V'

//DIRECTION CONSTANTS
//R -> right or forward 
//L -> left or backward
#define POSITIVE_DIR 'R'
#define NEGATIVE_DIR 'L'

//DEFINING OUTPUT PINS
//ACTION pins
//car pins
#define ACCELERATION_R_PIN 26
#define ACCELERATION_L_PIN 27
#define STEERING_R_PIN 14
#define STEERING_L_PIN 12
//arm pins
#define ARM_ROTATION_R_PIN 13
#define ARM_ROTATION_L_PIN 15
#define TILTING_R_PIN 5
#define TILTING_L_PIN 17
#define CLAW_ACT_R_PIN 16
#define CLAW_ACT_L_PIN 4
#define LIFT_R_PIN 19
#define LIFT_L_PIN 18
//VELOCIY pins
//car vel pins
#define CAR_VEL1_PIN 32
#define CAR_VEL2_PIN 33
#define CAR_VEL3_PIN 25
//arm vel pins
#define ARM_VEL1_PIN 23
#define ARM_VEL2_PIN 22
#define ARM_VEL3_PIN 21

#endif
