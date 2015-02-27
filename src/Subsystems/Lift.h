#ifndef Lift_H
#define Lift_H

#include "WPILib.h"
#include "AdvPIDController.h"

static const double kLiftRate = 0.05;

static const double kLiftBottom = 0.1;  //~Bottom of lift
static const double kLiftTop = 2.4;  //~Top of lift
static const double kLiftStackIn = 0.61;  //Height for intake of already stacked boxes

static const double kRightOff = 0.787;
static const double kLeftOff = 1.678;
static const float kLeftP = 10;
static const float kLeftI = 0.5;
static const float kLeftD = 4;
static const float kLeftV = 0;
static const float kRightP = 10;
static const float kRightI = 0.5;
static const float kRightD = 4;
static const float kRightV = 0;
static const float kLiftPeriod = 0.01;

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
	Solenoid *leftClamp;
	Solenoid *rightClamp;
	void ClampOn();
	void ClampOff();
	AdvPIDController *leftPID, *rightPID;
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
	bool IsPIDEnabled();
	void EnablePID();
	void DisablePID();
	bool SetTarget(double target, double rate = 100);
	bool OnTarget();
	void PIDJogUp(double rate = 0.003);
	void PIDJogDown(double rate = 0.003);
	void PIDJogStop();
	void LiftUp();
	void LiftDown();
	void LiftStop();
	void RightLiftUp();
	void RightLiftDown();
	void LeftLiftUp();
	void LeftLiftDown();
	void printLiftValues(void);
	bool lb;
	bool lt;
	bool rb;
	bool rt;
};

#endif
