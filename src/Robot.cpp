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
	Compressor *c = new Compressor(10);
	IMAQdxSession session;
	Image *frame;
	IMAQdxError imaqError;
	void RobotInit() override {
		CommandBase::init();
		//autonomousCommand = new exampleCommand();
		//lw = LiveWindow::GetInstance();
		c -> SetClosedLoopControl(true);
	    // create an image
		frame = imaqCreateImage(IMAQ_IMAGE_RGB, 0);
		//the camera name (ex "cam0") can be found through the roborio web interface
		imaqError = IMAQdxOpenCamera("cam0", IMAQdxCameraControlModeController, &session);
		if(imaqError != IMAQdxErrorSuccess) {
			DriverStation::ReportError("IMAQdxOpenCamera error: " + std::to_string((long)imaqError) + "\n");
		}
		imaqError = IMAQdxConfigureGrab(session);
		if(imaqError != IMAQdxErrorSuccess) {
			DriverStation::ReportError("IMAQdxConfigureGrab error: " + std::to_string((long)imaqError) + "\n");
		}
	}
	
	void DisabledPeriodic() override
	{
		Scheduler::GetInstance()->Run();
		c -> SetClosedLoopControl(true);
	}

	void AutonomousInit() override
	{
		c -> SetClosedLoopControl(true);
		if (autonomousCommand != NULL)
			autonomousCommand->Start();


	}

	void AutonomousPeriodic() override
	{
		CommandBase::chassis->mecanumDrive(1,0,0);
		Scheduler::GetInstance()->Run();
	}

	void TeleopInit() override
	{
		// This makes sure that the autonomous stops running when
		// teleop starts running. If you want the autonomous to 
		// continue until interrupted by another command, remove
		// this line or comment it out.
		if (autonomousCommand != NULL)
			autonomousCommand->Cancel();
		//driveCommand.start();
		c->SetClosedLoopControl(true);
	}

	void TeleopPeriodic() override
	{
		Scheduler::GetInstance()->Run();
		IMAQdxGrab(session, frame, true, NULL);
			if(imaqError != IMAQdxErrorSuccess) {
				DriverStation::ReportError("IMAQdxGrab error: " + std::to_string((long)imaqError) + "\n");
			} else {
				imaqDrawShapeOnImage(frame, frame, { 10, 10, 100, 100 }, DrawMode::IMAQ_DRAW_VALUE, ShapeMode::IMAQ_SHAPE_OVAL, 0.0f);
				CameraServer::GetInstance()->SetImage(frame);
			}
			Wait(0.005);
	}

	void TestPeriodic() override
	{
		//lw->Run();
	}
};

START_ROBOT_CLASS(Robot);

