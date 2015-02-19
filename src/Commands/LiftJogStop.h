#ifndef LiftJogStop_H
#define LiftJogStop_H

#include "../CommandBase.h"
#include "WPILib.h"

class LiftJogStop: public CommandBase
{
public:
	LiftJogStop();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
