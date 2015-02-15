#include "Lift_Up.h"

Lift_Up::Lift_Up()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	Requires(lift);
}

// Called just before this Command runs the first time
void Lift_Up::Initialize()
{
	lift->EnablePID();
}

// Called repeatedly when this Command is scheduled to run
void Lift_Up::Execute()
{

	lift->PIDUp((((oi->GetBoxingJoystick())->GetZ())+1)/20);
}

// Make this return true when this Command no longer needs to run execute()
bool Lift_Up::IsFinished()
{
	return lift->OnTarget();
}

// Called once after isFinished returns true
void Lift_Up::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Lift_Up::Interrupted()
{

}
