#include "ToteUnClamp.h"

ToteUnClamp::ToteUnClamp()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	Requires(lift);
}

// Called just before this Command runs the first time
void ToteUnClamp::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void ToteUnClamp::Execute()
{
lift->ClampOff();
}

// Make this return true when this Command no longer needs to run execute()
bool ToteUnClamp::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void ToteUnClamp::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ToteUnClamp::Interrupted()
{

}
