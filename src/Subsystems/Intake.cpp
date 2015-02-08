#include "Intake.h"
#include "../RobotMap.h"

Intake::Intake() :	Subsystem("Intake")
{
	leftIntakeWheel = new CANTalon(ch_leftIntakeWheel);
	rightIntakeWheel = new CANTalon(ch_rightIntakeWheel);
	leftIntake = new Solenoid(ch_LeftIntake);
	rightIntake = new Solenoid(ch_RightIntake);
	ultrasonic = new AnalogInput(ch_Ultrasonic);
	distance = 0;

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
void Intake::AutoIntake(){
if(GetDistance()>2.5){
leftIntake -> Set(true);
rightIntake -> Set(true);
leftIntakeWheel -> Set(1.0);
rightIntakeWheel -> Set(-1.0);
}
else if(GetDistance()<=2 && GetDistance()>=2.5){	//These Values need to be just when the box gets to the wheel
leftIntake -> Set(true);
rightIntake -> Set(true);
leftIntakeWheel -> Set(1.0);
rightIntakeWheel -> Set(-1.0);
}
else{
leftIntake -> Set(false);
rightIntake -> Set(false);
leftIntakeWheel -> Set(0);
rightIntakeWheel -> Set(0);
}
}
double Intake::GetDistance(){
	double rawdistance=ultrasonic->GetVoltage();
	distance = ((rawdistance/.0124))/12;
	return distance;
}
