#include "WPILib.h"
#include "Commands/Command.h"
//#include "Commands/ExampleCommand.h"
#include "CommandBase.h"
#include "Commands/Drive.h"
#include "RobotMap.h"


class Robot: public IterativeRobot
{
private:
	Command *driveCommand;
	Command *autonomousCommand;
	LiveWindow *lw;
	//Compressor *c;

	void RobotInit()
	{
		CommandBase::init();
		//autonomousCommand = new exampleCommand();
		lw = LiveWindow::GetInstance();
		//c -> SetClosedLoopControl(true);
		//driveCommand = new Drive();
	}
	
	void DisabledPeriodic()
	{
		Scheduler::GetInstance()->Run();
		//c -> SetClosedLoopControl(true);
	}

	void AutonomousInit()
	{
		//c -> SetClosedLoopControl(true);
		if (autonomousCommand != NULL)
			autonomousCommand->Start();


	}

	void AutonomousPeriodic()
	{
		CommandBase::chassis->mecanumDrive(1,0,0);
		Scheduler::GetInstance()->Run();
	}

	void TeleopInit()
	{
		// This makes sure that the autonomous stops running when
		// teleop starts running. If you want the autonomous to 
		// continue until interrupted by another command, remove
		// this line or comment it out.
		if (autonomousCommand != NULL)
			autonomousCommand->Cancel();
		//driveCommand.start();
	}

	void TeleopPeriodic()
	{
		Scheduler::GetInstance()->Run();
	}

	void TestPeriodic()
	{
		lw->Run();
	}
};

START_ROBOT_CLASS(Robot);

