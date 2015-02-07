#include "OI.h"
#include "Commands/Close_Intake.h"
#include "Commands/Coopertition_Setpoint.h"
#include "Commands/Drive.h"
#include "Commands/IntakeCommand.h"
#include "Commands/Lift_Down.h"
#include "Commands/Lift_Up.h"
#include "Commands/Open_Intake.h"
#include "Commands/Outtake.h"
#include "RobotMap.h"

OI::OI()
{
	// Process operator interface input here.
	driveStick = new Joystick(ch_driveStick);
	boxingStick = new Joystick(ch_boxingStick);
	rollerinButton = new JoystickButton(boxingStick, ch_rollerinButton);
	rolleroutButton = new JoystickButton(boxingStick, ch_rolleroutButton);
	intakeclampButton = new JoystickButton(boxingStick, ch_intakeclampButton);
	intakeletgoButton = new JoystickButton(boxingStick, ch_intakeletgoButton);
	pickupButton = new JoystickButton(boxingStick, ch_pickupButton);
	setdownButton = new JoystickButton(boxingStick, ch_setdownButton);
	coopertitionButton = new JoystickButton(boxingStick, ch_coopertitionButton);

	//set the buttons to commands
	rollerinButton -> WhenPressed(new IntakeCommand());
	rolleroutButton -> WhenPressed(new Outtake());
	intakeclampButton -> WhenPressed(new Close_Intake());
	intakeletgoButton -> WhenPressed(new Open_Intake());
	pickupButton -> WhenPressed(new Lift_Up());
	setdownButton -> WhenPressed(new Lift_Down());
	coopertitionButton -> WhenPressed(new Coopertition_Setpoint());

}
Joystick * OI::GetDriveJoystick()
{
	return driveStick;
}
Joystick * OI::GetBoxingJoystick()
{
	return boxingStick;
}
