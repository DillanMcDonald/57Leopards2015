#include <Commands/LiftBottom.h>

LiftBottom::LiftBottom()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	Requires(lift);
}

// Called just before this Command runs the first time
void LiftBottom::Initialize()
{
	if (!lift->IsPIDEnabled()) lift->EnablePID();
	lift->SetTarget(0.1, kLiftRate);
}

// Called repeatedly when this Command is scheduled to run
void LiftBottom::Execute()
{
}

// Make this return true when this Command no longer needs to run execute()
bool LiftBottom::IsFinished()
{
	return lift->OnTarget();
}

// Called once after isFinished returns true
void LiftBottom::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void LiftBottom::Interrupted()
{

}
