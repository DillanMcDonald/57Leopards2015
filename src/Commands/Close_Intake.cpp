#include "Close_Intake.h"

Close_Intake::Close_Intake()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	Requires(intake);
}

// Called just before this Command runs the first time
void Close_Intake::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void Close_Intake::Execute()
{
	if(!intake->ClampClose())intake->ClampClose();
}

// Make this return true when this Command no longer needs to run execute()
bool Close_Intake::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void Close_Intake::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Close_Intake::Interrupted()
{

}
