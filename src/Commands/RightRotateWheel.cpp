#include "RightRotateWheel.h"

RightRotateWheel::RightRotateWheel()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	Requires(intake);
}

// Called just before this Command runs the first time
void RightRotateWheel::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void RightRotateWheel::Execute()
{
	intake->RightRotate();
}

// Make this return true when this Command no longer needs to run execute()
bool RightRotateWheel::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void RightRotateWheel::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RightRotateWheel::Interrupted()
{

}
