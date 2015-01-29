#ifndef Close_Intake_H
#define Close_Intake_H

#include "../CommandBase.h"
#include "WPILib.h"

class Close_Intake: public CommandBase
{
public:
	Close_Intake();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
