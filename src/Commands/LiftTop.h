#ifndef LiftTop_H
#define LiftTop_H

#include "../CommandBase.h"
#include "WPILib.h"

class LiftTop: public CommandBase
{
public:
	LiftTop();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
