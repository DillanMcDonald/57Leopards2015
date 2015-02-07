#include "Chassis.h"
#include "../RobotMap.h"
#include "Joystick.h"

Chassis::Chassis() :Subsystem("Chassis"){
frontleftm = new CANTalon(ch_FrontLeftM);
frontrightm = new CANTalon(ch_FrontRightM);
backleftm = new CANTalon(ch_BackLeftM);
backrightm = new CANTalon(ch_BackRightM);
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
	drive->MecanumDrive_Polar(drivestick->GetRawAxis(0), drivestick->GetRawAxis(1), drivestick->GetRawAxis(2));
}

void Chassis::mecanumDrive_Polar(double x, double y, double z){
	drive->MecanumDrive_Polar(x,y,z);
}

