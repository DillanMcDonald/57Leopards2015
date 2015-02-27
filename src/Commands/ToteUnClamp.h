#ifndef ToteUnClamp_H
#define ToteUnClamp_H

#include "../CommandBase.h"
#include "WPILib.h"

class ToteUnClamp: public CommandBase
{
public:
	ToteUnClamp();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
