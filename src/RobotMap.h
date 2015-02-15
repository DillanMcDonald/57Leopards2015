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
static const uint32_t ch_Open = 1;
static const uint32_t ch_Close = 0;

// Joysticks
static const uint32_t ch_driveStick = 0;
static const uint32_t ch_boxingStick = 1;

//Buttons on the Drive Joystick
static const uint32_t ch_manualLeftUp = 7;
static const uint32_t ch_manualLeftDown = 9;
static const uint32_t ch_manualRightUp = 8;
static const uint32_t ch_manualRightDown = 10;

//Buttons on the Manipulator Joystick
static const uint32_t ch_intakeclampButton = 1;
static const uint32_t ch_rolleroutButton = 2;
static const uint32_t ch_rollerinButton = 3;
static const uint32_t ch_rightwheelrotate = 4;
static const uint32_t ch_leftwheelrotate =5;
static const uint32_t ch_LiftUp=6;
static const uint32_t ch_LiftDown=7;
static const uint32_t ch_coopertitionButton= 8;
static const uint32_t ch_PIDLiftDown = 10;
static const uint32_t ch_PIDLiftUp = 11;
//unused channel designators

static const uint32_t ch_intakeletgoButton= 2;
static const uint32_t ch_pickupButton = 4;
static const uint32_t ch_setdownButton = 7;

//Digital IO
static const uint32_t ch_LeftLeadTopLimit = 1;
static const uint32_t ch_RightLeadBotLimit =3;
static const uint32_t ch_LeftLeadBotLimit = 0;
static const uint32_t ch_RightLeadTopLimit =2;


//Analog IO
static const uint32_t ch_LeftLeadscrewPot = 1;
static const uint32_t ch_RightLeadscrewPot = 2;
static const uint32_t ch_Ultrasonic =3;

#endif
