#include <Commands/LiftCoopertition.h>

LiftCoopertition::LiftCoopertition()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	Requires(lift);
}

// Called just before this Command runs the first time
void LiftCoopertition::Initialize()
{
	if (!lift->IsPIDEnabled()) lift->EnablePID();
	lift->SetTarget(1.207, kLiftRate);
}

// Called repeatedly when this Command is scheduled to run
void LiftCoopertition::Execute()
{
}

// Make this return true when this Command no longer needs to run execute()
bool LiftCoopertition::IsFinished()
{
	return lift->OnTarget();
}

// Called once after isFinished returns true
void LiftCoopertition::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void LiftCoopertition::Interrupted()
{

}
