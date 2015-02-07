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
	double GetDistance();
	Solenoid *leftIntake;
	Solenoid *rightIntake;
	CANTalon *leftIntakeWheel;
	CANTalon *rightIntakeWheel;
	AnalogInput *ultrasonic;
	double distance;
};

#endif
