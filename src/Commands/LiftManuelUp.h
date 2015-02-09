#ifndef LiftManuelUp_H
#define LiftManuelUp_H

#include "../CommandBase.h"
#include "WPILib.h"

class LiftManuelUp: public CommandBase
{
public:
	LiftManuelUp();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
