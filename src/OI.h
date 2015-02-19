#ifndef OI_H
#define OI_H

#include "WPILib.h"

class OI
{
private:

public:
	OI();
	Joystick *driveStick;
	Joystick *boxingStick;
	JoystickButton *rollerinButton;
	JoystickButton *rolleroutButton;
	JoystickButton *intakeclampButton;
	JoystickButton *intakeletgoButton;
	JoystickButton *pickupButton;
	JoystickButton *setdownButton;
	JoystickButton *coopertitionButton;
	JoystickButton *rightWheelRotate;
	JoystickButton *leftWheelRotate;
	JoystickButton *liftTop;
	JoystickButton *liftBottom;
	JoystickButton *manualLeftUp;
	JoystickButton *manualLeftDown;
	JoystickButton *manualRightUp;
	JoystickButton *manualRightDown;
	JoystickButton *jogliftup;
	JoystickButton *jogliftdown;
	Joystick *GetDriveJoystick();
	Joystick *GetBoxingJoystick();
};

#endif
