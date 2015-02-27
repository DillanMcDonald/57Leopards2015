#ifndef DriveForwardsDistance_H
#define DriveForwardsDistance_H

#include "../CommandBase.h"
#include "WPILib.h"

class DriveForwardsDistance: public CommandBase
{
public:
	DriveForwardsDistance();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
