#ifndef LiftStop_H
#define LiftStop_H

#include "../CommandBase.h"
#include "WPILib.h"

class LiftStop: public CommandBase
{
public:
	LiftStop();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
