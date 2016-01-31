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
	double x=drivestick->GetY();
	double y=drivestick->GetX();
	double z=drivestick->GetZ();
	//Wait(0.01);
	/*frontrightm->Set(-(x+y+z));
	frontleftm->Set((x+y-z));
	backrightm->Set(-(x-y+z));
	backleftm->Set((x-y-z));*/
	frontrightm->Set(y+x);
	frontleftm->Set(y-x);
	backrightm->Set(y+x);
	backleftm->Set(y-x);

	//SmartDashboard::PutNumber("Encoder Velocity (FR)", frontrightm->GetEncVel());
	//SmartDashboard::PutNumber("Encoder Velocity (BR)", backrightm->GetEncVel());
	//SmartDashboard::PutNumber("Encoder Velocity (BL)", backleftm->GetEncVel());
	//SmartDashboard::PutNumber("Encoder Velocity (FL)", frontleftm->GetEncVel());
}

/*void Chassis::mecanumDrive(double y, double x, double z, double targetfr, double targetbr, double targetbl, double targetfl){
	//drive->MecanumDrive_Cartesian(x,y,z);
	//Wait(0.01);
	if(frontrightm->GetEncVel() != targetfr){
		frontrightm->Set(-(x+y+z));
	}
	else{
		frontrightm->Set(0);
	}
	if(backrightm->GetEncVel() != targetbr){
		backrightm->Set(-(x-y+z));
	}
	else{
		backrightm->Set(0);
	}
	if(frontleftm->GetEncVel() != targetfl){
		frontleftm->Set((x+y-z));
	}
	else{
		frontleftm->Set(0);
	}
	if(backleftm->GetEncVel() != targetbl){
		backleftm->Set((x-y-z));
	}
	else{
		 backleftm->Set(0);
	}



	frontleftm->Set((x+y-z));
	backrightm->Set(-(x-y+z));
	backleftm->Set((x-y-z));

}
*/
