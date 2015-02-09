#ifndef Lift_H
#define Lift_H

#include "WPILib.h"

class Lift: public Subsystem
{
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	 float leftliftheight;
	 float rightliftheight;
	 bool isSet;
	double lastLeftHeight, lastRightHeight, leftMotorOut, rightMotorOut,threshold;
public:
	Lift();
	void InitDefaultCommand();
	CANTalon *leftLeadscrew;
	CANTalon *rightLeadscrew;
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
	AnalogInput *leftlift_pot;
	DigitalInput *leftlifttop_limit;
	DigitalInput *leftliftbot_limit;
	AnalogInput *rightlift_pot;
	DigitalInput *rightlifttop_limit;
	DigitalInput *rightliftbot_limit;
	float currentleftheight;
	float currentrightheight;
	bool leftTopIsThere;
	bool rightTopIsThere;
	bool leftBotIsThere;
	bool rightBotIsThere;
	bool liftLevel;
	void LiftLevel();
	float leftLiftHeight;
	float rightLiftHeight;
	void LiftUp();
	void LiftDown();
	void LiftStop();
};

#endif
