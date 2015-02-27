#include "ToteClamp.h"

ToteClamp::ToteClamp()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	Requires(lift);
}

// Called just before this Command runs the first time
void ToteClamp::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void ToteClamp::Execute()
{
	lift->ClampOn();
}

// Make this return true when this Command no longer needs to run execute()
bool ToteClamp::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void ToteClamp::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ToteClamp::Interrupted()
{

}
