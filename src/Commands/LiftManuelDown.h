#ifndef LiftManuelDown_H
#define LiftManuelDown_H

#include "../CommandBase.h"
#include "WPILib.h"

class LiftManuelDown: public CommandBase
{
public:
	LiftManuelDown();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
