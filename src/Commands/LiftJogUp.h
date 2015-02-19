#ifndef LiftJogUp_H
#define LiftJogUp_H

#include "../CommandBase.h"
#include "WPILib.h"

class LiftJogUp: public CommandBase
{
public:
	LiftJogUp();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
