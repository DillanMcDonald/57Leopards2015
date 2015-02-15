#include "LiftManuelDown.h"

LiftManuelDown::LiftManuelDown()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	Requires(lift);
}

// Called just before this Command runs the first time
void LiftManuelDown::Initialize()
{
	lift->EnablePID();
}

// Called repeatedly when this Command is scheduled to run
void LiftManuelDown::Execute()
{
	lift->SetTarget(0.05, .2);
}

// Make this return true when this Command no longer needs to run execute()
bool LiftManuelDown::IsFinished()
{
	return lift->OnTarget();
}

// Called once after isFinished returns true
void LiftManuelDown::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void LiftManuelDown::Interrupted()
{

}
