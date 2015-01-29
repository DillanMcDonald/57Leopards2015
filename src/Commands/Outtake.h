#ifndef Outtake_H
#define Outtake_H

#include "../CommandBase.h"
#include "WPILib.h"

class Outtake: public CommandBase
{
public:
	Outtake();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
