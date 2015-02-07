#include "Open_Intake.h"

Open_Intake::Open_Intake()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	Requires(intake);
}

// Called just before this Command runs the first time
void Open_Intake::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void Open_Intake::Execute()
{
	intake->ClampOpen();
}

// Make this return true when this Command no longer needs to run execute()
bool Open_Intake::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void Open_Intake::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Open_Intake::Interrupted()
{

}
