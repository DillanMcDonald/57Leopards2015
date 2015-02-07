#include "Coopertition_Setpoint.h"

Coopertition_Setpoint::Coopertition_Setpoint()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	Requires(lift);
}

// Called just before this Command runs the first time
void Coopertition_Setpoint::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void Coopertition_Setpoint::Execute()
{
	lift->SetLeftLiftHeight(0.5);
	lift->SetRightLiftHeight(0.5);
}

// Make this return true when this Command no longer needs to run execute()
bool Coopertition_Setpoint::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void Coopertition_Setpoint::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Coopertition_Setpoint::Interrupted()
{

}
