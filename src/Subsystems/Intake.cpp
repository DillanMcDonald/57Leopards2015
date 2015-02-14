#include "Intake.h"
#include "../RobotMap.h"

Intake::Intake() :	Subsystem("Intake")
{
	leftIntakeWheel = new CANTalon(ch_leftIntakeWheel);
	rightIntakeWheel = new CANTalon(ch_rightIntakeWheel);
	intakeOpen = new Solenoid(10,ch_Open);
	intakeClose = new Solenoid(10,ch_Close);
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
void Intake::BoxJoystick(Joystick *boxingstick){
	double x=boxingstick->GetY();
	double y=boxingstick->GetX();
	leftIntakeWheel -> Set(x);
	rightIntakeWheel -> Set(x);
}

void Intake::PullIn(){
leftIntakeWheel -> Set(1.0);
rightIntakeWheel -> Set(-1.0);

}
void Intake::LeftRotate(){
	leftIntakeWheel -> Set(1.0);
	rightIntakeWheel -> Set(1.0);

}
void Intake::RightRotate(){
	leftIntakeWheel -> Set(-1.0);
	rightIntakeWheel -> Set(-1.0);

}
void Intake::PushOut(){
leftIntakeWheel -> Set(-1.0);
rightIntakeWheel -> Set(1.0);
}
void Intake::ClampClose(){
intakeClose->Set(true);
intakeOpen->Set(false);
}
void Intake::RollerStop(){
leftIntakeWheel -> Set(0);
rightIntakeWheel -> Set(0);

}
void Intake::ClampOpen(){
intakeOpen->Set(true);
intakeClose->Set(false);
}
/*void Intake::AutoIntake(){
if(GetDistance()>2.5){
openIntake -> Set(true);
closeIntake -> Set(false);
leftIntakeWheel -> Set(1.0);
rightIntakeWheel -> Set(-1.0);
}
else if(GetDistance()<=2 && GetDistance()>=2.5){	//These Values need to be just when the box gets to the wheel
openIntake -> Set(false);
closeIntake -> Set(true);
leftIntakeWheel -> Set(1.0);
rightIntakeWheel -> Set(-1.0);
}
else{
openIntake -> Set(true);
closeIntake -> Set(false);
leftIntakeWheel -> Set(0);
rightIntakeWheel -> Set(0);
}
}
double Intake::GetDistance(){
	double rawdistance=ultrasonic->GetVoltage();
	distance = ((rawdistance/.0124))/12;
	return distance;
}
*/
