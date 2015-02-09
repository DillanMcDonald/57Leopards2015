#include "LiftStop.h"

LiftStop::LiftStop()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	Requires(lift);
}

// Called just before this Command runs the first time
void LiftStop::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void LiftStop::Execute()
{
	lift->LiftStop();
}

// Make this return true when this Command no longer needs to run execute()
bool LiftStop::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void LiftStop::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void LiftStop::Interrupted()
{

}
