#include "JoystickIntake.h"

JoystickIntake::JoystickIntake()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	Requires(intake);
}

// Called just before this Command runs the first time
void JoystickIntake::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void JoystickIntake::Execute()
{
	intake->BoxJoystick(oi->GetBoxingJoystick());
}

// Make this return true when this Command no longer needs to run execute()
bool JoystickIntake::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void JoystickIntake::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void JoystickIntake::Interrupted()
{

}
