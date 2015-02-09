#include "LeftRotateWheel.h"

LeftRotateWheel::LeftRotateWheel()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	Requires(intake);
}

// Called just before this Command runs the first time
void LeftRotateWheel::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void LeftRotateWheel::Execute()
{
intake->LeftRotate();
}

// Make this return true when this Command no longer needs to run execute()
bool LeftRotateWheel::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void LeftRotateWheel::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void LeftRotateWheel::Interrupted()
{

}
