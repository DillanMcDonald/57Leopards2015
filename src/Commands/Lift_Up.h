#ifndef Lift_Up_H
#define Lift_Up_H

#include "../CommandBase.h"
#include "WPILib.h"

class Lift_Up: public CommandBase
{
public:
	Lift_Up();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
