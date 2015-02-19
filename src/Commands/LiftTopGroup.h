#ifndef LiftTopGroup_H
#define LiftTopGroup_H

#include <Commands/LiftTop.h>
#include "Commands/CommandGroup.h"
#include "Open_Intake.h"
#include "Close_Intake.h"
#include "WPILib.h"

class LiftTopGroup: public CommandGroup
{
public:
	LiftTopGroup();
};

#endif
