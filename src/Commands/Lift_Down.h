#ifndef Lift_Down_H
#define Lift_Down_H

#include "../CommandBase.h"
#include "WPILib.h"

class Lift_Down: public CommandBase
{
public:
	Lift_Down();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
