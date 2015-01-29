#ifndef Open_Intake_H
#define Open_Intake_H

#include "../CommandBase.h"
#include "WPILib.h"

class Open_Intake: public CommandBase
{
public:
	Open_Intake();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
