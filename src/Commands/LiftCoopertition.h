#ifndef LiftCoopertition_H
#define LiftCoopertition_H

#include "../CommandBase.h"
#include "WPILib.h"

class LiftCoopertition: public CommandBase
{
public:
	LiftCoopertition();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
