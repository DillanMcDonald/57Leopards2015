#include "RollerStop.h"

RollerStop::RollerStop()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	Requires(intake);
}

// Called just before this Command runs the first time
void RollerStop::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void RollerStop::Execute()
{
	intake->RollerStop();
}

// Make this return true when this Command no longer needs to run execute()
bool RollerStop::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void RollerStop::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RollerStop::Interrupted()
{

}
