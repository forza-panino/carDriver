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
#define CAR_VEL1_PIN 25
#define CAR_VEL2_PIN 26
#define CAR_VEL3_PIN 27
//arm vel pins
#define ARM_VEL1_PIN 21
#define ARM_VEL2_PIN 19
#define ARM_VEL3_PIN 18

#endif
