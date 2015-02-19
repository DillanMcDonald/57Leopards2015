#include "Lift.h"
#include "../RobotMap.h"

Lift::Lift() :Subsystem("Lift")
{
leftLeadscrew= new CANTalon(ch_LeftLeadM);
rightLeadscrew = new CANTalon(ch_RightLeadM);
leftlift_pot = new AnalogInput(ch_LeftLeadscrewPot);
rightlift_pot = new AnalogInput(ch_RightLeadscrewPot);
threshold = .05;
leftlifttop_limit  = new DigitalInput(ch_LeftLeadTopLimit);
leftliftbot_limit  = new DigitalInput(ch_LeftLeadBotLimit);
rightlifttop_limit  = new DigitalInput(ch_RightLeadTopLimit);
rightliftbot_limit  = new DigitalInput(ch_RightLeadBotLimit);
leftTopIsThere = false;
rightTopIsThere = false;
leftBotIsThere = false;
rightBotIsThere = false;
leftPID = new AdvPIDController(kLeftP, kLeftI, kLeftD, 0.0f, kLeftV, leftlift_pot, leftLeadscrew, leftlifttop_limit, leftliftbot_limit, kLiftPeriod);
rightPID = new AdvPIDController(kRightP, kRightI, kRightD, 0.0f, kRightV, rightlift_pot, rightLeadscrew, rightlifttop_limit, rightliftbot_limit, kLiftPeriod);
leftPID->SetAbsoluteTolerance(threshold);
rightPID->SetAbsoluteTolerance(threshold);
leftPID->SetAutoReset(threshold/2);
rightPID->SetAutoReset(threshold/2);
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
}

void Lift::RightLiftUp(){
	rightLeadscrew->Set(0.5);
}

void Lift::RightLiftDown(){
	rightLeadscrew->Set(-0.5);
}

void Lift::LeftLiftUp(){
	rightLeadscrew->Set(0.5);
}

void Lift::LeftLiftDown(){
	rightLeadscrew->Set(-0.5);
}

void Lift::LiftStop(){
	leftLeadscrew->Set(0);
	rightLeadscrew->Set(0);
}

void Lift::EnablePID(){
	leftPID->Enable();
	rightPID->Enable();
	return;
}

void Lift::DisablePID(){
	leftPID->Disable();
	rightPID->Disable();
	return;
}

/**
 * Set the setpoint for the Lift PID system
 * @param target the desired setpoint
 * @param rate change from previous setpoint will be limited to this value.  Default 5 (instant)
 */
bool Lift::SetTarget(double target, double rate){
	leftPID->SetSetpoint(target + kLeftOff, rate);
	rightPID->SetSetpoint(target + kRightOff, rate);
	return OnTarget();
}

bool Lift::OnTarget(){
	return (leftPID->OnTarget() && rightPID->OnTarget());
}


/**
 * Start the Lift setpoint jogging up at a specified rate
 * @param rate amount to increase setpoint per period
 */
void Lift::PIDJogUp(double rate){
	leftPID->SetJog(rate);
	rightPID->SetJog(rate);
}

/**
 * Bump the Lift setpoint jogging down at a specified rate
 * @param rate amount to decrease setpoint per period
 */
void Lift::PIDJogDown(double rate){
	leftPID->SetJog(-rate);
	rightPID->SetJog(-rate);
}

/**
 * Stop the lift jogging
 */
void Lift::PIDJogStop(){
	leftPID->DisableJog();
	rightPID->DisableJog();
}

bool Lift::IsPIDEnabled()
{
	return leftPID->IsEnabled() && rightPID->IsEnabled();
}

void Lift::printLiftValues(void){
	SmartDashboard::PutNumber("Pot Sample Rate", leftlift_pot->GetSampleRate());
	SmartDashboard::PutNumber("Pot Average Bits", leftlift_pot->GetAverageBits());
	SmartDashboard::PutNumber("Left Lift Position", leftlift_pot->PIDGet());
	SmartDashboard::PutNumber("Right Lift Position", rightlift_pot->PIDGet());
	SmartDashboard::PutNumber("Left Lift Cmd", leftPID->Get());
	SmartDashboard::PutNumber("Right Lift Cmd", rightPID->Get());
	SmartDashboard::PutNumber("Left Lift Tgt", leftPID->GetSetpoint());
	SmartDashboard::PutNumber("Right Lift Tgt", rightPID->GetSetpoint());
	SmartDashboard::PutNumber("Left Lift Err", leftPID->GetError());
	SmartDashboard::PutNumber("Right Lift Err", rightPID->GetError());
	SmartDashboard::PutBoolean("Left Lift Ena", leftPID->IsEnabled());
	SmartDashboard::PutBoolean("Right Lift Ena", rightPID->IsEnabled());
	SmartDashboard::PutBoolean("Lift On Tgt", OnTarget());
	SmartDashboard::PutBoolean("Left Lift On Tgt", leftPID->OnTarget());
	SmartDashboard::PutBoolean("Right Lift On Tgt", rightPID->OnTarget());
	SmartDashboard::PutBoolean("Left Limit Top", leftlifttop_limit->Get());
	SmartDashboard::PutBoolean("Left Limit Bottom", leftliftbot_limit->Get());
	SmartDashboard::PutBoolean("Right Limit Top", rightlifttop_limit->Get());
	SmartDashboard::PutBoolean("Right Limit Bottom", rightliftbot_limit->Get());
}


