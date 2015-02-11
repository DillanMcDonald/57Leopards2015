#ifndef JoystickIntake_H
#define JoystickIntake_H

#include "../CommandBase.h"
#include "WPILib.h"

class JoystickIntake: public CommandBase
{
public:
	JoystickIntake();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
