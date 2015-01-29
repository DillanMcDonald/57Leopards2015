#ifndef Coopertition_Setpoint_H
#define Coopertition_Setpoint_H

#include "../CommandBase.h"
#include "WPILib.h"

class Coopertition_Setpoint: public CommandBase
{
public:
	Coopertition_Setpoint();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
