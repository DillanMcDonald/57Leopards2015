#ifndef Chassis_H
#define Chassis_H

#include "Commands/Subsystem.h"
#include "WPILib.h"

class Chassis: public Subsystem
{
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	RobotDrive *drive;
public:
	Chassis();
	void InitDefaultCommand();
	void DriveWithJoystick(Joystick *drivestick);
	void mecanumDrive_Polar(double x, double y, double z);
	CANTalon *frontleftm;
	CANTalon *frontrightm;
	CANTalon *backleftm;
	CANTalon *backrightm;

};

#endif
