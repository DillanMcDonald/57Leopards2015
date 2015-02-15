#include "Lift.h"
#include "../RobotMap.h"

Lift::Lift() :Subsystem("Lift")
{
leftLeadscrew= new CANTalon(ch_LeftLeadM);
rightLeadscrew = new CANTalon(ch_RightLeadM);
leftlift_pot = new AnalogInput(ch_LeftLeadscrewPot);
rightlift_pot = new AnalogInput(ch_RightLeadscrewPot);
threshold = .04;
leftlifttop_limit  = new DigitalInput(ch_LeftLeadTopLimit);
leftliftbot_limit  = new DigitalInput(ch_LeftLeadBotLimit);
rightlifttop_limit  = new DigitalInput(ch_RightLeadTopLimit);
rightliftbot_limit  = new DigitalInput(ch_RightLeadBotLimit);
leftTopIsThere = false;
rightTopIsThere = false;
leftBotIsThere = false;
rightBotIsThere = false;
leftPID = new PIDController(kLeftP, kLeftI, kLeftD, leftlift_pot, leftLeadscrew);
rightPID = new PIDController(kRightP, kRightI, kRightD, rightlift_pot, rightLeadscrew);
leftPID->SetAbsoluteTolerance(threshold);
rightPID->SetAbsoluteTolerance(threshold);
lastLeftHeight =1;
lastRightHeight =1;
leftLeadscrew->SetPID(0.0,0.0,0.0,0.0);
rightLeadscrew->SetPID(0.0,0.0,0.0,0.0);

}

void Lift::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

bool Lift::SetLeftLiftHeight(float setleftheight){
	bool atsetheight =0;
	leftLiftHeight= GetLeftHeight();
	if(leftLiftHeight!=setleftheight && leftlifttop_limit == 0 && leftliftbot_limit == 0){
		if(leftLiftHeight<setleftheight){
			leftLeadscrew->Set(1.0);
		}
		else{
			leftLeadscrew->Set(-1.0);
		}
		atsetheight=0;
	}
	else{
		atsetheight=1;
	}
	return atsetheight;
}
bool Lift::SetRightLiftHeight(float setrightheight){
	rightLiftHeight=GetRightHeight();
	bool atsetheight =0;
	if(rightLiftHeight!=setrightheight && rightlifttop_limit == 0 && rightliftbot_limit == 0){
		if(rightLiftHeight<setrightheight){
			rightLeadscrew->Set(1.0);
		}
		else{
			rightLeadscrew->Set(-1.0);
		}
		atsetheight=0;
	}
	else{
		atsetheight=1;
	}
	return atsetheight;
}

void Lift::LiftLevel(){					//Checks if the right lift is level with the left lift and if not sets them to be equal
	leftLiftHeight = GetLeftHeight();
	rightLiftHeight = GetRightHeight();
	leftTopIsThere = leftlifttop_limit->Get();
	leftBotIsThere = leftliftbot_limit->Get();
	rightTopIsThere = rightlifttop_limit->Get();
	rightBotIsThere = rightliftbot_limit->Get();
	if (leftLiftHeight != rightLiftHeight){		//if the left lift doesn't equal the right lift
		liftLevel=false;
	}
	else if(leftTopIsThere == true && rightTopIsThere != true){	//then if the left top limit is toggled and the right top is not, return false
		liftLevel = false;
	}
	else if(leftBotIsThere == true && rightBotIsThere != true){ //else if the left bottom limit is toggled nad the right is not, return false
			liftLevel = false;
		}
	else if(rightTopIsThere == true && leftTopIsThere == true){ //else if both of the top limits are toggled return true
		liftLevel = true;
	}
	else if(leftBotIsThere == true && rightBotIsThere == true){ //else if both of the bottom limits are toggled return true
			liftLevel = true;
		}
	else if(leftliftheight == rightliftheight){ //else if the potentiometer values are equal return true
				liftLevel = true;
			}
	else if(leftliftheight != rightliftheight){ //else if the potentiometer values are different return false
					liftLevel = false;
				}
	else{
		liftLevel = true; //else return true
	}
	if(liftLevel != true){ //if the lift is not level, set the left lift to the same height as the right lift
		SetLeftLiftHeight(rightLiftHeight);
	}
	liftLevel = true; //then return true
}
float Lift::GetLeftHeight() {
	leftliftheight = leftlift_pot->GetVoltage();     //Returns the height of the left lift
	return leftliftheight;
}
float Lift::GetRightHeight(){
	rightliftheight = rightlift_pot->GetVoltage();	//Returns the height of the right lift
	return rightliftheight;
}
void Lift::LiftUp(){
	lt = leftlifttop_limit->Get();
	rt = rightlifttop_limit->Get();
	if(lt == 1 && rt == 0){
		leftLeadscrew->Set(0);
		rightLeadscrew->Set(1);
	}
	else if(rt == 1 && lt==0){
		rightLeadscrew->Set(0);
		leftLeadscrew->Set(1);
	}
	else if(rt == 1 && lt == 1){
		leftLeadscrew->Set(0);
		rightLeadscrew->Set(0);
	}
	else{
		leftLeadscrew->Set(1.0);
		rightLeadscrew->Set(1.0);
	}
	printLiftValues();
}
void Lift::LiftDown(){
	lb = leftliftbot_limit->Get();
	rb = rightliftbot_limit->Get();
	if(lb == 1 && rb ==0){
		leftLeadscrew->Set(0);
		rightLeadscrew->Set(-1);
	}
	else if(rb == 1 && lb == 0){
		rightLeadscrew->Set(0);
		leftLeadscrew->Set(-1);
	}
	else if(rb == 1 && lb == 1){
			leftLeadscrew->Set(0);
			rightLeadscrew->Set(0);
		}
	else{
		leftLeadscrew->Set(-1.0);
		rightLeadscrew->Set(-1.0);
	}
	printLiftValues();
}

void Lift::RightLiftUp(){
	rightLeadscrew->Set(0.5);
	printLiftValues();
}

void Lift::RightLiftDown(){
	rightLeadscrew->Set(-0.5);
	printLiftValues();
}

void Lift::LeftLiftUp(){
	rightLeadscrew->Set(0.5);
	printLiftValues();
}

void Lift::LeftLiftDown(){
	rightLeadscrew->Set(-0.5);
	printLiftValues();
}

void Lift::LiftStop(){
	leftLeadscrew->Set(0);
	rightLeadscrew->Set(0);
	printLiftValues();
}

void Lift::EnablePID(){
	double lv, rv, av;
	lv = leftlift_pot->PIDGet() - kLeftOff;
	rv = rightlift_pot->PIDGet() - kRightOff;
	av = (lv + rv) / 2;
	SetTarget(av);
	leftPID->Enable();
	rightPID->Enable();
	return;
}

void Lift::DisablePID(){
	leftPID->Disable();
	rightPID->Disable();
	leftLeadscrew->Set(0.0);
	rightLeadscrew->Set(0.0);
	incSetpoint = 0;
	return;
}

/**
 * Set the setpoint for the Lift PID system
 * @param target the desired setpoint
 * @param rate change from previous setpoint will be limited to this value.  Default 5 (instant)
 */
bool Lift::SetTarget(double target, double rate){
	double inc = target - curSetpoint;
	lb = leftliftbot_limit->Get();
	rb = rightliftbot_limit->Get();
	if (fabs(inc) <= rate)
	{
		curSetpoint = target;
		incSetpoint = 0;
	}
	/*else if((lb == 1 || rb==1)||(lb==1 && rb==1)){
		if(target<curSetpoint){
			target = curSetpoint;
		}
	}*/
	else{
		incSetpoint = inc;
		curSetpoint += (inc < 0) ? -rate : rate;
	}

	leftPID->SetSetpoint(curSetpoint + kLeftOff);
	rightPID->SetSetpoint(curSetpoint + kRightOff);
	return OnTarget();
	printLiftValues();
}

bool Lift::OnTarget(){
	return ((incSetpoint == 0) && leftPID->OnTarget() && rightPID->OnTarget());
}


/**
 * Bump the Lift setpoint up a specific amount.  Call repeatedly for smooth
 * motion upwards while PID enabled
 * @param rate amount to increase setpoint by
 */
void Lift::PIDUp(double rate){
	SetTarget(curSetpoint + rate);
	printLiftValues();
}

/**
 * Bump the Lift setpoint dowb a specific amount.  Call repeatedly for smooth
 * motion upwards while PID enabled
 * @param rate amount to decrease setpoint by
 */
void Lift::PIDDown(double rate){
	SetTarget(curSetpoint - rate);
	printLiftValues();
}

void Lift::printLiftValues(void){
	SmartDashboard::PutNumber("Left Lift Position", leftlift_pot->PIDGet());
	SmartDashboard::PutNumber("Right Lift Position", rightlift_pot->PIDGet());
	SmartDashboard::PutBoolean("Left Limit Top", leftlifttop_limit->Get());
	SmartDashboard::PutBoolean("Left Limit Bottom", leftliftbot_limit->Get());
	SmartDashboard::PutBoolean("Right Limit Top", rightlifttop_limit->Get());
	SmartDashboard::PutBoolean("Right Limit Bottom", rightliftbot_limit->Get());
}


