#include <Commands/LiftJogUp.h>

LiftJogUp::LiftJogUp()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	Requires(lift);
}

// Called just before this Command runs the first time
void LiftJogUp::Initialize()
{
	if (!lift->IsPIDEnabled()) lift->EnablePID();
}

// Called repeatedly when this Command is scheduled to run
void LiftJogUp::Execute()
{
	lift->PIDJogUp((((oi->GetBoxingJoystick())->GetZ())+1)/50);
}

// Make this return true when this Command no longer needs to run execute()
bool LiftJogUp::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void LiftJogUp::End()
{
	lift->PIDJogStop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void LiftJogUp::Interrupted()
{
	lift->PIDJogStop();
}
