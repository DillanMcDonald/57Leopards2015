#ifndef LiftBottom_H
#define LiftBottom_H

#include "../CommandBase.h"
#include "WPILib.h"

class LiftBottom: public CommandBase
{
public:
	LiftBottom();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
