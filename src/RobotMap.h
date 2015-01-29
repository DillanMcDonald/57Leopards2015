#ifndef ROBOTMAP_H
#define ROBOTMAP_H

#include "WPILib.h"

/**
 * The RobotMap is a mapping from the ports sensors and actuators are wired into
 * to a variable name. This provides flexibility changing wiring, makes checking
 * the wiring easier and significantly reduces the number of magic numbers
 * floating around.
 */
 
// For example to map the left and right motors, you could define the
// following variables to use with your drivetrain subsystem.
//const int LEFTMOTOR = 1;
//const int RIGHTMOTOR = 2;

// If you are using multiple modules, make sure to define both the port
// number and the module. For example you with a rangefinder:
//const int RANGE_FINDER_PORT = 1;
//const int RANGE_FINDER_MODULE = 1;

//CAN VictorSP for Chassis
static const uint32_t ch_FrontLeftM = 1;
static const uint32_t ch_BackLeftM = 2;
static const uint32_t ch_BackRightM = 3;
static const uint32_t ch_FrontRightM = 4;


//CAN VictorSP for Leadscrew
static const uint32_t ch_LeftLeadM = 5;
static const uint32_t ch_RightLeadM = 6;


//Relay Constants
static const uint32_t ch_intakewheels = 7;

//Solenoid channels
static const uint32_t ch_LeftIntake = 8;
static const uint32_t ch_RightIntake = 9;

//Digital IO

//Analog IO

// Joysticks
static const uint32_t ch_driveStick = 1;
static const uint32_t ch_boxingStick = 2;

//Buttons
static const uint32_t ch_coopertitionButton= 1;
static const uint32_t ch_intakeclampButton = 2;
static const uint32_t ch_intakeletgoButton= 3;
static const uint32_t ch_pickupButton = 4;
static const uint32_t ch_rollerinButton = 5;
static const uint32_t ch_rolleroutButton = 6;
static const uint32_t ch_setdownButton = 7;


#endif
