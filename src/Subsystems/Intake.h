#ifndef Intake_H
#define Intake_H

#include "Commands/Subsystem.h"
#include "WPILib.h"

class Intake: public Subsystem
{
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
public:
	Intake();
	void InitDefaultCommand();
	void PullIn();
	void PushOut();
	void ClampClose();
	void ClampOpen();
	void AutoIntake();
	void RollerStop();
	double GetDistance();
	Solenoid *intakeOpen;
	Solenoid *intakeClose;
	CANTalon *leftIntakeWheel;
	CANTalon *rightIntakeWheel;
	AnalogInput *ultrasonic;
	double distance;
	void LeftRotate();
	void RightRotate();
	void BoxJoystick(Joystick *boxingstick);
};

#endif
