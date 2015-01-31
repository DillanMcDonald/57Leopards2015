#ifndef Lift_H
#define Lift_H

#include "WPILib.h"
#include "../AdvPIDSubsystem.h"

class Lift: public PIDSubsystem
{
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	 float leftliftheight;
	 float rightliftheight;
	 bool isSet;
	// set the P, I, and D constants here
	static const double Kp = 0.0;
	static const double Ki = 0.0;
	static const double Kd = 0.0;
	static const double Kf = 0.0;
	static const bool inverted = false;

	static const double MinOutput = -1.0;
	static const double MaxOutput = 1.0;

	static const double MinInput = 0.08;
	static const double MaxInput = 1.0;

	static const double AbsErr = 0.01;

	double lastLeftHeight, lastRightHeight, leftMotorOut, rightMotorOut,threshold;
public:
	Lift();
	void InitDefaultCommand();
	VictorSP *leftLeadscrew;
	VictorSP *rightLeadscrew;
	double ReturnPIDInput();
	void UsePIDOutput(double output);
	bool LeftLiftSpeed(float speed);
	bool RightLiftSpeed(float speed);
	float GetLeftHeight();
	float GetRightHeight();
    bool SetLeftLiftHeight(float setleftheight);
    bool SetRightLiftHeight(float setrightheight);
	bool isLiftSet();
	double GetLeftOutput();
	double GetRightOutput();
	bool IsEnabled();
	AnalogInput *leftlift_pot;
	DigitalInput *leftlift_limit;
	AnalogInput *rightlift_pot;
	DigitalInput *rightlift_limit;
	float currentleftheight;
	float currentrightheight;
	bool leftIsThere;
	bool rightIsThere;
	bool liftLevel;
	void LiftLevel();
	float leftLiftHeight;
	float rightLiftHeight;
};

#endif
