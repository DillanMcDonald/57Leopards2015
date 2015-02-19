#include <Commands/LiftTop.h>

LiftTop::LiftTop()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	Requires(lift);
}

// Called just before this Command runs the first time
void LiftTop::Initialize()
{
	if (!lift->IsPIDEnabled()) lift->EnablePID();
	lift->SetTarget(2.12, kLiftRate);
}

// Called repeatedly when this Command is scheduled to run
void LiftTop::Execute()
{
}

// Make this return true when this Command no longer needs to run execute()
bool LiftTop::IsFinished()
{
	return lift->OnTarget();
}

// Called once after isFinished returns true
void LiftTop::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void LiftTop::Interrupted()
{

}
