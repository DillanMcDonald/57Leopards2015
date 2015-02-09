#include "LiftManuelUp.h"

LiftManuelUp::LiftManuelUp()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	Requires(lift);
}

// Called just before this Command runs the first time
void LiftManuelUp::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void LiftManuelUp::Execute()
{
	lift->LiftUp();
}

// Make this return true when this Command no longer needs to run execute()
bool LiftManuelUp::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void LiftManuelUp::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void LiftManuelUp::Interrupted()
{

}
