#include "Intake.h"

Intake::Intake()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
}

// Called just before this Command runs the first time
void Intake::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void Intake::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool Intake::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void Intake::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Intake::Interrupted()
{

}
