#include <Commands/LiftBottom.h>
#include <Commands/LiftCoopertition.h>
#include <Commands/LiftJogDown.h>
#include <Commands/LiftJogStop.h>
#include <Commands/LiftJogUp.h>
#include <Commands/LiftTop.h>
#include "OI.h"
#include "Commands/Close_Intake.h"
#include "Commands/Drive.h"
#include "Commands/IntakeCommand.h"
#include "Commands/Open_Intake.h"
#include "Commands/Outtake.h"
#include "Commands/RollerStop.h"
#include "Commands/LeftRotateWheel.h"
#include "Commands/RightRotateWheel.h"
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
	liftTop = new JoystickButton(boxingStick, ch_LiftUp);
	liftBottom = new JoystickButton(boxingStick, ch_LiftDown);
	manualLeftUp = new JoystickButton(driveStick, ch_manualLeftUp);
	manualLeftDown = new JoystickButton(driveStick, ch_manualLeftDown);
	manualRightUp = new JoystickButton(driveStick, ch_manualRightUp);
	manualRightDown = new JoystickButton(driveStick, ch_manualRightDown);
	jogliftup = new JoystickButton(boxingStick, ch_PIDLiftUp);
	jogliftdown = new JoystickButton(boxingStick, ch_PIDLiftDown);

	//set the buttons to commands
	rollerinButton -> WhenPressed(new IntakeCommand());
	rollerinButton -> WhenReleased(new RollerStop());
	rolleroutButton -> WhenPressed(new Outtake());
	rolleroutButton -> WhenReleased(new RollerStop());
	intakeclampButton -> WhenPressed(new Close_Intake());
	intakeclampButton -> WhenReleased(new Open_Intake());
	coopertitionButton -> WhenPressed(new LiftCoopertition());
	rightWheelRotate-> WhenPressed(new RightRotateWheel());
	rightWheelRotate-> WhenReleased(new RollerStop());
	leftWheelRotate-> WhenPressed(new LeftRotateWheel());
	leftWheelRotate-> WhenReleased(new RollerStop());
	liftTop-> WhenPressed(new LiftTop());
	//manuelLiftUp-> WhenReleased(new Lift_PIDStop());
	liftBottom-> WhenPressed(new LiftBottom());
	//manuelLiftDown-> WhenReleased(new Lift_PIDStop());
	jogliftup-> WhenPressed(new LiftJogUp());
	jogliftup-> WhenReleased(new LiftJogStop());
	jogliftdown-> WhenPressed(new LiftJogDown());
	jogliftdown-> WhenReleased(new LiftJogStop());

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
