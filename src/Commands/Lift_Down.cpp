#include "Lift_Down.h"

Lift_Down::Lift_Down()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	Requires(lift);
}

// Called just before this Command runs the first time
void Lift_Down::Initialize()
{
	lift->EnablePID();
}

// Called repeatedly when this Command is scheduled to run
void Lift_Down::Execute()
{

lift->PIDDown((((oi->GetBoxingJoystick())->GetZ())+1)/20);
}

// Make this return true when this Command no longer needs to run execute()
bool Lift_Down::IsFinished()
{
	return lift->OnTarget();
}

// Called once after isFinished returns true
void Lift_Down::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Lift_Down::Interrupted()
{

}
