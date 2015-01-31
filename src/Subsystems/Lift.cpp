#include "Lift.h"
#include "../RobotMap.h"

Lift::Lift() :PIDSubsystem("Lift", Kp, Ki, Kd)
{
leftLeadscrew= new VictorSP(ch_LeftLeadM);
rightLeadscrew = new VictorSP(ch_RightLeadM);
leftlift_pot = new AnalogInput(ch_LeftLeadscrewPot);
rightlift_pot = new AnalogInput(ch_RightLeadscrewPot);
threshold = .02;
leftlift_limit  = new DigitalInput(ch_LeftLeadLimit);
rightlift_limit  = new DigitalInput(ch_RightLeadLimit);
leftIsThere = false;
rightIsThere = false;
lastLeftHeight =1;
lastRightHeight =1;

/*Adv*/PIDController *controller = GetPIDController();

controller->SetInputRange(MinInput, MaxInput);
controller->SetOutputRange(MinOutput, MaxOutput);
controller->SetAbsoluteTolerance(AbsErr);

}

void Lift::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

double Lift::ReturnPIDInput() {
	// Return your input value for the PID loop
	// e.g. a sensor, like a potentiometer:
	// yourPot->SetAverageVoltage() / kYourMaxVoltage;
    leftliftheight = leftlift_pot->GetVoltage();
    rightliftheight = rightlift_pot ->GetVoltage();
	return leftliftheight;
	return rightliftheight;
}
double Lift::GetLeftOutput() {
	return leftMotorOut;
}
double Lift::GetRightOutput(){
	return rightMotorOut;
}
void Lift::UsePIDOutput(double output) {
	// Use output to drive your system, like a motor
	// e.g. yourMotor->Set(output);
	leftMotorOut = inverted ? -output : output;
	rightMotorOut= inverted ? -output : output;
		leftLeadscrew->Set(leftMotorOut);
		rightLeadscrew->Set(rightMotorOut);
}
bool Lift::IsEnabled()
{
	return GetPIDController()->IsEnabled();
}
bool Lift::LeftLiftSpeed(float speed){        // Controls the speed of the left leadscrew for the lift
	currentleftheight = GetLeftHeight();
	leftIsThere = leftlift_limit->Get();
	if(speed > 0.0)
	{
		if (currentleftheight > 1.95||leftIsThere == true)
		{
			leftLeadscrew->Set(0);
			leftIsThere = true;
		} else
		{
			leftLeadscrew->Set(speed);
			leftIsThere = false;
		}

	} else if (speed < 0.0)
	{
		if(currentleftheight <.3 )
		{
			leftLeadscrew->Set(0);
			leftIsThere = true;
		} else
		{
			leftLeadscrew->Set(speed);
			leftIsThere = false;
		}
	} else
	{
		leftLeadscrew->Set(0);
		leftIsThere = true;
		return leftIsThere;
}
	return leftIsThere;
}
bool Lift::RightLiftSpeed(float speed){        // Controls the speed of the right leadscrew for the lift
	currentrightheight = GetRightHeight();
	rightIsThere = rightlift_limit->Get();
	if(speed > 0.0)
	{
		if ( currentrightheight > 1.95 ||rightIsThere==true)
		{
			rightLeadscrew->Set(0);
			rightIsThere = true;
		} else
		{
			rightLeadscrew->Set(speed);
			rightIsThere = false;
		}

	} else if (speed < 0.0)
	{
		if( currentrightheight <.3)
		{
			rightLeadscrew->Set(0);
			rightIsThere = true;
		} else
		{
			rightLeadscrew->Set(speed);
			rightIsThere = false;
		}
	} else
	{
		rightLeadscrew->Set(0);
		rightIsThere = true;	}
		return rightIsThere;
}

float Lift::GetLeftHeight() {
	leftliftheight = leftlift_pot->GetVoltage();     //Returns the height of the Lift
	return leftliftheight;
}
float Lift::GetRightHeight(){
	rightliftheight = rightlift_pot->GetVoltage();
	return rightliftheight;
}
bool Lift::SetLeftLiftHeight(float setleftheight){ //Sets the height of the lift by comparing it to that
	bool limited;
	currentleftheight = GetLeftHeight();            //of the current lift height
	if (currentleftheight  < setleftheight - threshold) {        //Know which direction is up
		limited = LeftLiftSpeed(.4);
		return limited;
	} else if (currentleftheight > setleftheight + threshold ) {  //If the height is below
		limited = LeftLiftSpeed(-.6);
		return limited;
	} else {
		LeftLiftSpeed(0);
		return true;
	}
}
bool Lift::SetRightLiftHeight(float setrightheight){ //Sets the height of the lift by comparing it to that
	bool limited;
	currentrightheight = GetRightHeight();            //of the current lift height
	if (currentrightheight  < setrightheight - threshold) {        //Know which direction is up
		limited = RightLiftSpeed(.4);
		return limited;
	} else if (currentrightheight > setrightheight + threshold ) {  //If the height is below
		limited = RightLiftSpeed(-.6);
		return limited;
	} else {
		RightLiftSpeed(0);
		return true;
	}
}
void Lift::LiftLevel(){
	leftLiftHeight = GetLeftHeight();
	rightLiftHeight = GetRightHeight();
	leftIsThere = leftlift_limit->Get();
	rightIsThere = rightlift_limit->Get();
	if (leftLiftHeight ==! rightLiftHeight){
		liftLevel=false;
	}
	else if(leftIsThere == true && rightIsThere ==! true){
		liftLevel = false;
	}
	else if(rightIsThere == true && leftIsThere ==! true){
		liftLevel = false;
	}
	if(liftLevel ==! true){
		SetLeftLiftHeight(rightLiftHeight);
	}
	liftLevel = true;
}
