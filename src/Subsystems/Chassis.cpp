#include "Chassis.h"
#include "../RobotMap.h"

Chassis::Chassis() :Subsystem("Chassis"){
frontleftm = new VictorSP(ch_FrontLeftM);
frontrightm = new VictorSP(ch_FrontRightM);
backleftm = new VictorSP(ch_BackLeftM);
backrightm = new VictorSP(ch_BackRightM);
drive = new RobotDrive(frontleftm, backleftm, frontrightm, backrightm);
drive = new RobotDrive(frontleftm, backleftm, frontrightm, backrightm);
drive->SetSafetyEnabled(kMotorSafety);

}

void Chassis::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
	//SetDefaultCommand(new Drive());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
void Chassis::DriveWithJoystick(Joystick *drivestick)
{
	drive->MecanumDrive_Polar(drivestick);
}

void Chassis::mecanumDrive_Polar(double x, double y, double z){
	drive->MecanumDrive_Polar(x,y,z);
}

