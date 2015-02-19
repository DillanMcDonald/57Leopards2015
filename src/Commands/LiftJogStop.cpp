#include <Commands/LiftJogStop.h>

LiftJogStop::LiftJogStop()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	Requires(lift);
}

// Called just before this Command runs the first time
void LiftJogStop::Initialize()
{
	if (!lift->IsPIDEnabled()) lift->EnablePID();
}

// Called repeatedly when this Command is scheduled to run
void LiftJogStop::Execute()
{
	lift->PIDJogStop();
}

// Make this return true when this Command no longer needs to run execute()
bool LiftJogStop::IsFinished()
{
	return true;
}

// Called once after isFinished returns true
void LiftJogStop::End()
{
	lift->PIDJogStop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void LiftJogStop::Interrupted()
{
	lift->PIDJogStop();
}
