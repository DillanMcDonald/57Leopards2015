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
#include "Commands/JoystickIntake.h"
#include "RobotMap.h"

OI::OI()
{
	// Process operator interface input here.
	driveStick = new Joystick(ch_driveStick);
	boxingStick = new Joystick(ch_boxingStick);
	rollerinButton = new JoystickButton(boxingStick, ch_rollerinButton);
	rolleroutButton = new JoystickButton(boxingStick, ch_rolleroutButton);
	intakeclampButton = new JoystickButton(boxingStick, ch_intakeclampButton);
	//pickupButton = new JoystickButton(boxingStick, ch_pickupButton);
	//setdownButton = new JoystickButton(boxingStick, ch_setdownButton);
	coopertitionButton = new JoystickButton(boxingStick, ch_coopertitionButton);
	rightWheelRotate = new JoystickButton(boxingStick, ch_rightwheelrotate);
	leftWheelRotate = new JoystickButton(boxingStick, ch_leftwheelrotate);
	manuelLiftUp = new JoystickButton(boxingStick, ch_LiftUp);
	manuelLiftDown = new JoystickButton(boxingStick, ch_LiftDown);
	manualLeftUp = new JoystickButton(driveStick, ch_manualLeftUp);
	manualLeftDown = new JoystickButton(driveStick, ch_manualLeftDown);
	manualRightUp = new JoystickButton(driveStick, ch_manualRightUp);
	manualRightDown = new JoystickButton(driveStick, ch_manualRightDown);
	pidliftup = new JoystickButton(boxingStick, ch_PIDLiftUp);
	pidliftdown = new JoystickButton(boxingStick, ch_PIDLiftDown);

	//set the buttons to commands
	rollerinButton -> WhenPressed(new IntakeCommand());
	rollerinButton -> WhenReleased(new RollerStop());
	rolleroutButton -> WhenPressed(new Outtake());
	rolleroutButton -> WhenReleased(new RollerStop());
	intakeclampButton -> WhenPressed(new Close_Intake());
	intakeclampButton -> WhenReleased(new Open_Intake());
	coopertitionButton -> WhenPressed(new Coopertition_Setpoint());
	rightWheelRotate-> WhenPressed(new RightRotateWheel());
	rightWheelRotate-> WhenReleased(new RollerStop());
	leftWheelRotate-> WhenPressed(new LeftRotateWheel());
	leftWheelRotate-> WhenReleased(new RollerStop());
	manuelLiftUp-> WhenPressed(new LiftManuelUp());
	//manuelLiftUp-> WhenReleased(new LiftStop());
	manuelLiftDown-> WhenPressed(new LiftManuelDown());
	//manuelLiftDown-> WhenReleased(new LiftStop());
	pidliftup-> WhenPressed(new Lift_Up());
	pidliftup-> WhenReleased(new LiftStop());
	pidliftdown-> WhenPressed(new Lift_Down());
	pidliftdown-> WhenReleased(new LiftStop());

	/*manualLeftUp->WhenPressed(new LeftLiftUp());
	manualLeftUp->WhenReleased(new LiftStop());
	manualLeftDown->WhenPressed(new LeftLiftDown());
	manualLeftDown->WhenReleased(new LiftStop());

	manualRightUp->WhenPressed(new RightLiftUp());
	manualRightUp->WhenReleased(new LiftStop());
	manualRightDown->WhenPressed(new RightLiftDown());
	manualRightDown->WhenReleased(new LiftStop())
	*/

}
Joystick * OI::GetDriveJoystick()
{
	return driveStick;
}
Joystick * OI::GetBoxingJoystick()
{
	return boxingStick;
}
