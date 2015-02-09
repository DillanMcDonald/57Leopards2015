#ifndef RollerStop_H
#define RollerStop_H

#include "../CommandBase.h"
#include "WPILib.h"

class RollerStop: public CommandBase
{
public:
	RollerStop();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
