#include "OI.h"
#include "Commands/Close_Intake.h"
#include "Commands/Coopertition_Setpoint.h"
#include "Commands/Drive.h"
#include "Commands/IntakeCommand.h"
#include "Commands/Lift_Down.h"
#include "Commands/Lift_Up.h"
#include "Commands/Open_Intake.h"
#include "Commands/Outtake.h"
#include "Commands/RollerStop.h"
#include "Commands/LeftRotateWheel.h"
#include "Commands/RightRotateWheel.h"
#include "Commands/LiftManuelUp.h"
#include "Commands/LiftManuelDown.h"
#include "Commands/LiftStop.h"
#include "RobotMap.h"

OI::OI()
{
	// Process operator interface input here.
	driveStick = new Joystick(ch_driveStick);
	boxingStick = new Joystick(ch_boxingStick);
	rollerinButton = new JoystickButton(driveStick, ch_rollerinButton);
	rolleroutButton = new JoystickButton(driveStick, ch_rolleroutButton);
	intakeclampButton = new JoystickButton(driveStick, ch_intakeclampButton);
	intakeletgoButton = new JoystickButton(driveStick, ch_intakeletgoButton);
	pickupButton = new JoystickButton(boxingStick, ch_pickupButton);
	setdownButton = new JoystickButton(boxingStick, ch_setdownButton);
	coopertitionButton = new JoystickButton(boxingStick, ch_coopertitionButton);
	rightWheelRotate = new JoystickButton(driveStick, ch_rightwheelrotate);
	leftWheelRotate = new JoystickButton(driveStick, ch_leftwheelrotate);
	manuelLiftUp = new JoystickButton(driveStick, ch_LiftUp);
	manuelLiftDown = new JoystickButton(driveStick, ch_LiftDown);

	//set the buttons to commands
	rollerinButton -> WhenPressed(new IntakeCommand());
	rollerinButton -> WhenReleased(new RollerStop());
	rolleroutButton -> WhenPressed(new Outtake());
	rolleroutButton -> WhenReleased(new RollerStop());
	intakeclampButton -> WhenPressed(new Close_Intake());
	intakeletgoButton -> WhenReleased(new Open_Intake());
	pickupButton -> WhenPressed(new Lift_Up());
	setdownButton -> WhenPressed(new Lift_Down());
	coopertitionButton -> WhenPressed(new Coopertition_Setpoint());
	rightWheelRotate-> WhenPressed(new RightRotateWheel());
	rightWheelRotate-> WhenReleased(new RollerStop());
	leftWheelRotate-> WhenPressed(new LeftRotateWheel());
	leftWheelRotate-> WhenReleased(new RollerStop());
	manuelLiftUp-> WhenPressed(new LiftManuelUp());
	manuelLiftUp-> WhenReleased(new LiftStop());
	manuelLiftDown-> WhenPressed(new LiftManuelDown());
	manuelLiftDown-> WhenReleased(new LiftStop());

}
Joystick * OI::GetDriveJoystick()
{
	return driveStick;
}
Joystick * OI::GetBoxingJoystick()
{
	return boxingStick;
}
