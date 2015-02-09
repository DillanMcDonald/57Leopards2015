#ifndef ROBOTMAP_H
#define ROBOTMAP_H

#include "WPILib.h"

/**
 * The RobotMap is a mapping from the ports sensors and actuators are wired into
 * to a variable name. This provides flexibility changing wiring, makes checking
 * the wiring easier and significantly reduces the number of magic numbers
 * floating around.
 */
 static const bool kMotorSafety = false;
// For example to map the left and right motors, you could define the
// following variables to use with your drivetrain subsystem.
//const int LEFTMOTOR = 1;
//const int RIGHTMOTOR = 2;

// If you are using multiple modules, make sure to define both the port
// number and the module. For example you with a rangefinder:
//const int RANGE_FINDER_PORT = 1;
//const int RANGE_FINDER_MODULE = 1;

//CAN VictorSP for Chassis
static const uint32_t ch_FrontLeftM = 3;
static const uint32_t ch_BackLeftM = 4;
static const uint32_t ch_BackRightM = 1;
static const uint32_t ch_FrontRightM = 2;


//CAN VictorSP for Leadscrew
static const uint32_t ch_LeftLeadM = 5;
static const uint32_t ch_RightLeadM = 7;


//CAN VictorSP for Intake Wheels
static const uint32_t ch_leftIntakeWheel = 6;
static const uint32_t ch_rightIntakeWheel = 8;

//Solenoid channels
static const uint32_t ch_Open = 0;
static const uint32_t ch_Close = 1;

// Joysticks
static const uint32_t ch_driveStick = 0;
static const uint32_t ch_boxingStick = 1;

//Buttons
static const uint32_t ch_coopertitionButton= 1;
static const uint32_t ch_intakeclampButton = 1;
static const uint32_t ch_intakeletgoButton= 2;
static const uint32_t ch_pickupButton = 4;
static const uint32_t ch_rollerinButton = 5;
static const uint32_t ch_rolleroutButton = 6;
static const uint32_t ch_setdownButton = 7;
static const uint32_t ch_rightwheelrotate = 4;
static const uint32_t ch_leftwheelrotate =3;
static const uint32_t ch_LiftUp=11;
static const uint32_t ch_LiftDown=12;

//Digital IO
static const uint32_t ch_LeftLeadTopLimit = 0;
static const uint32_t ch_RightLeadBotLimit =3;
static const uint32_t ch_LeftLeadBotLimit = 1;
static const uint32_t ch_RightLeadTopLimit =2;


//Analog IO
static const uint32_t ch_LeftLeadscrewPot = 1;
static const uint32_t ch_RightLeadscrewPot = 2;
static const uint32_t ch_Ultrasonic =3;

#endif
