
#include "OI.h"
#include "Commands/Drive.h"
#include "RobotMap.h"

OI::OI()
{
	// Process operator interface input here.
	driveStick = new Joystick(ch_driveStick);

	//set the buttons to commands

}
Joystick * OI::GetDriveJoystick()
{
	return driveStick;
}
