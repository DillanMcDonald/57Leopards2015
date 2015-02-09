#ifndef LeftRotateWheel_H
#define LeftRotateWheel_H

#include "../CommandBase.h"
#include "WPILib.h"

class LeftRotateWheel: public CommandBase
{
public:
	LeftRotateWheel();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
