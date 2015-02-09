#include "Lift.h"
#include "../RobotMap.h"

Lift::Lift() :Subsystem("Lift")
{
leftLeadscrew= new CANTalon(ch_LeftLeadM);
rightLeadscrew = new CANTalon(ch_RightLeadM);
leftlift_pot = new AnalogInput(ch_LeftLeadscrewPot);
rightlift_pot = new AnalogInput(ch_RightLeadscrewPot);
threshold = .02;
leftlifttop_limit  = new DigitalInput(ch_LeftLeadTopLimit);
leftliftbot_limit  = new DigitalInput(ch_LeftLeadBotLimit);
rightlifttop_limit  = new DigitalInput(ch_RightLeadTopLimit);
rightliftbot_limit  = new DigitalInput(ch_RightLeadBotLimit);
leftTopIsThere = false;
rightTopIsThere = false;
leftBotIsThere = false;
rightBotIsThere = false;
lastLeftHeight =1;
lastRightHeight =1;
leftLeadscrew->SetPID(0.0,0.0,0.0,0.0);
rightLeadscrew->SetPID(0.0,0.0,0.0,0.0);
leftlifttop_limit=0;
leftliftbot_limit=0;
rightlifttop_limit=0;
rightliftbot_limit=0;
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
	if(leftlifttop_limit != 0){
		leftLeadscrew->Set(0);
	}
	else if(rightlifttop_limit != 0){
		rightLeadscrew->Set(0);
	}
	else{
		leftLeadscrew->Set(1.0);
		rightLeadscrew->Set(1.0);
	}

}
void Lift::LiftDown(){
	if(leftliftbot_limit != 0){
			leftLeadscrew->Set(0);
		}
		else if(rightliftbot_limit !=0){
			rightLeadscrew->Set(0);
		}
		else{
			leftLeadscrew->Set(-1.0);
			rightLeadscrew->Set(-1.0);
		}
}
void Lift::LiftStop(){
	leftLeadscrew->Set(0);
	rightLeadscrew->Set(0);
}
