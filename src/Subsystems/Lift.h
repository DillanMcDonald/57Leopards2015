#ifndef Lift_H
#define Lift_H

#include "WPILib.h"
#include "PIDController.h"


static const double kLiftBottom = 0.05;  //~Bottom of lift
static const double kLiftTop = 2.454;  //~Top of lift
static const double kLiftStackIn = 0.61;  //Height for intake of already stacked boxes

static const double kRightOff = 0.787;
static const double kLeftOff = 1.678;
static const float kLeftP = 8;
static const float kLeftI = 0;
static const float kLeftD = 1;
static const float kRightP = 8;
static const float kRightI = 0;
static const float kRightD = 1;

class Lift: public Subsystem
{
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	 float leftliftheight;
	 float rightliftheight;
	 bool isSet;
	 double curSetpoint, incSetpoint;
	double lastLeftHeight, lastRightHeight, leftMotorOut, rightMotorOut,threshold;
	void printLiftValues(void);
public:
	Lift();
	void InitDefaultCommand();
	CANTalon *leftLeadscrew;
	CANTalon *rightLeadscrew;
	PIDController *leftPID, *rightPID;
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
	void EnablePID();
	void DisablePID();
	bool SetTarget(double target, double rate = 5);
	bool OnTarget();
	void PIDUp(double rate = 0.015);
	void PIDDown(double rate = 0.015);
	void LiftUp();
	void LiftDown();
	void LiftStop();
	void RightLiftUp();
	void RightLiftDown();
	void LeftLiftUp();
	void LeftLiftDown();
	bool lb;
	bool lt;
	bool rb;
	bool rt;
};

#endif
