#ifndef LiftJogDown_H
#define LiftJogDown_H

#include "../CommandBase.h"
#include "WPILib.h"

class LiftJogDown: public CommandBase
{
public:
	LiftJogDown();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
