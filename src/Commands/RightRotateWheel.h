#ifndef RightRotateWheel_H
#define RightRotateWheel_H

#include "../CommandBase.h"
#include "WPILib.h"

class RightRotateWheel: public CommandBase
{
public:
	RightRotateWheel();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
