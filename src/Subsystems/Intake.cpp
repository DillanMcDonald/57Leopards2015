#include "Intake.h"
#include "../RobotMap.h"

Intake::Intake() :	Subsystem("Intake")
{
	leftIntakeWheel = new VictorSP(ch_leftIntakeWheel);
	rightIntakeWheel = new VictorSP(ch_rightIntakeWheel);
	leftIntake = new Solenoid(ch_LeftIntake);
	rightIntake = new Solenoid(ch_RightIntake);
}

void Intake::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
void Intake::PullIn(){
leftIntakeWheel -> Set(1.0);
rightIntakeWheel -> Set(-1.0);
}
void Intake::PushOut(){
leftIntakeWheel -> Set(-1.0);
rightIntakeWheel -> Set(1.0);
}
void Intake::ClampClose(){
leftIntake -> Set(true);
rightIntake -> Set(true);
}
void Intake::ClampOpen(){
leftIntake -> Set(false);
rightIntake -> Set(false);
}
