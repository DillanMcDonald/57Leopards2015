#ifndef ToteClamp_H
#define ToteClamp_H

#include "../CommandBase.h"
#include "WPILib.h"

class ToteClamp: public CommandBase
{
public:
	ToteClamp();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
