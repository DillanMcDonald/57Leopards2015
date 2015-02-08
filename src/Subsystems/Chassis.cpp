#include "Chassis.h"
#include "../RobotMap.h"
#include "Joystick.h"
#include "Commands/Drive.h"

Chassis::Chassis() :Subsystem("Chassis"){
frontleftm = new CANTalon(ch_FrontLeftM);
frontrightm = new CANTalon(ch_FrontRightM);
backleftm = new CANTalon(ch_BackLeftM);
backrightm = new CANTalon(ch_BackRightM);
//drive = new RobotDrive(frontleftm, backleftm, frontrightm, backrightm);
//drive->SetSafetyEnabled(kMotorSafety);

}

void Chassis::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
	SetDefaultCommand(new Drive());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
void Chassis::DriveWithJoystick(Joystick *drivestick)
{
	//drive->MecanumDrive_Polar(drivestick->GetRawAxis(0), drivestick->GetRawAxis(1), drivestick->GetRawAxis(2));
	//drive->MecanumDrive_Cartesian(drivestick->GetY(), drivestick->GetX(), drivestick->GetX(), 0);
	double x=drivestick->GetX();
	double y=drivestick->GetY();
	double z=drivestick->GetZ();
	//Wait(0.01);
	frontrightm->Set(x+y-z);
	frontleftm->Set(-(x-y+z));
	backrightm->Set(x-y-z);
	backleftm->Set(-(x+y+z));
}

void Chassis::mecanumDrive(double x, double y, double z){
	//drive->MecanumDrive_Cartesian(x,y,z);
	//Wait(0.01);
	frontrightm->Set(x+y-z);
	frontleftm->Set(-(x-y+z));
	backrightm->Set(x-y-z);
	backleftm->Set(-(x+y+z));
}

