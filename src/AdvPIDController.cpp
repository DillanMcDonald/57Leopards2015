/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.							  */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
/*----------------------------------------------------------------------------*/

#include "AdvPIDController.h"
#include "Notifier.h"
#include "PIDSource.h"
#include "PIDOutput.h"
#include "DigitalInput.h"
#include <math.h>
#include <vector>
#include "HAL/cpp/Synchronized.hpp"
#include "HAL/HAL.hpp"

static const char *kP = "p";
static const char *kI = "i";
static const char *kD = "d";
static const char *kF = "f";
static const char *kV = "v";
static const char *kSetpoint = "setpoint";
static const char *kEnabled = "enabled";


/**
 * Allocate a PID object with the given constants for P, I, D
 * @param Kp the proportional coefficient
 * @param Ki the integral coefficient
 * @param Kd the derivative coefficient
 * @param source The PIDSource object that is used to get values
 * @param output The PIDOutput object that is set to the output value
 * @param posLimit The DigitalInput object for the limit switch in the positive direction. Do not set if there's no limit switch
 * @param negLimit The DigitalInput object for the limit switch in the negative direction. Do not set if there's no limit switch
 * @param limitHit bool value of the limit switch when it is triggered
 * @param period the loop time for doing calculations. This particularly effects calculations of the
 * integral and differental terms. The default is 50ms.
 */
AdvPIDController::AdvPIDController(float Kp, float Ki, float Kd,
								PIDSource *source, PIDOutput *output,
								DigitalInput *posLimit, DigitalInput *negLimit, bool limitHit,
								float period) :
	m_semaphore (0)
{
	Initialize(Kp, Ki, Kd, 0.0f, 0.0f, source, output, posLimit, negLimit, limitHit, period);
}

/**
 * Allocate a PID object with the given constants for P, I, D
 * @param Kp the proportional coefficient
 * @param Ki the integral coefficient
 * @param Kd the derivative coefficient
 * @param Kf the feed forward coefficient
 * @param source The PIDSource object that is used to get values
 * @param output The PIDOutput object that is set to the output value
 * @param posLimit The DigitalInput object for the limit switch in the positive direction
 * @param negLimit The DigitalInput object for the limit switch in the negative direction
 * @param limitHit bool value of the limit switch when it is triggered
 * @param period the loop time for doing calculations. This particularly effects calculations of the
 * integral and differental terms. The default is 50ms.
 */
AdvPIDController::AdvPIDController(float Kp, float Ki, float Kd, float Kf,
								PIDSource *source, PIDOutput *output,
								DigitalInput *posLimit, DigitalInput *negLimit, bool limitHit,
								float period) :
	m_semaphore (0)
{
	Initialize(Kp, Ki, Kd, Kf, 0.0f, source, output, posLimit, negLimit, limitHit, period);
}

/**
 * Allocate a PID object with the given constants for P, I, D
 * @param Kp the proportional coefficient
 * @param Ki the integral coefficient
 * @param Kd the derivative coefficient
 * @param Kf the feed forward coefficient
 * @param Kv the velocity/rate feed forward coefficient
 * @param source The PIDSource object that is used to get values
 * @param output The PIDOutput object that is set to the output value
 * @param posLimit The DigitalInput object for the limit switch in the positive direction
 * @param negLimit The DigitalInput object for the limit switch in the negative direction
 * @param limitHit bool value of the limit switch when it is triggered
 * @param period the loop time for doing calculations. This particularly effects calculations of the
 * integral and differental terms. The default is 50ms.
 */
AdvPIDController::AdvPIDController(float Kp, float Ki, float Kd, float Kf, float Kv,
								PIDSource *source, PIDOutput *output,
								DigitalInput *posLimit, DigitalInput *negLimit, bool limitHit,
								float period) :
	m_semaphore (0)
{
	Initialize(Kp, Ki, Kd, Kf, Kv, source, output, posLimit, negLimit, limitHit, period);
}


void AdvPIDController::Initialize(float Kp, float Ki, float Kd, float Kf, float Kv,
								PIDSource *source, PIDOutput *output,
								DigitalInput *posLimit, DigitalInput *negLimit, bool limitHit,
								float period)
{
	m_table = NULL;
	
	m_semaphore = initializeMutexNormal();

	m_controlLoop = new Notifier(AdvPIDController::CallCalculate, this);

	m_P = Kp;
	m_I = Ki;
	m_D = Kd;
	m_F = Kf;
	m_V = Kv;

	m_maximumOutput = 1.0;
	m_minimumOutput = -1.0;

	m_maximumInput = 0;
	m_minimumInput = 0;

	m_continuous = false;
	m_enabled = false;
	m_setpoint = 0;

	m_prevError = 0;
	m_totalError = 0;
	m_tolerance = .05;

	m_result = 0;

	m_pidInput = source;
	m_pidOutput = output;
	m_posLimit = posLimit;
	m_negLimit = negLimit;
	m_limitHit = limitHit;
	m_period = period;
	m_autoReset = -1.0f;

	m_controlLoop->StartPeriodic(m_period);

	static int32_t instances = 0;
	instances++;
	HALReport(HALUsageReporting::kResourceType_PIDController, instances);

	m_toleranceType = kNoTolerance;
}

/**
 * Free the PID object
 */
AdvPIDController::~AdvPIDController()
{
	takeMutex(m_semaphore);
	deleteMutex(m_semaphore);
	delete m_controlLoop;
}

/**
 * Call the Calculate method as a non-static method. This avoids having to prepend
 * all local variables in that method with the class pointer. This way the "this"
 * pointer will be set up and class variables can be called more easily.
 * This method is static and called by the Notifier class.
 * @param controller the address of the PID controller object to use in the background loop
 */
void AdvPIDController::CallCalculate(void *controller)
{
	AdvPIDController *control = (AdvPIDController*) controller;
	control->Calculate();
}

 /**
  * Read the input, calculate the output accordingly, and write to the output.
  * This should only be called by the Notifier indirectly through CallCalculate
  * and is created during initialization.
  */
void AdvPIDController::Calculate()
{
	bool enabled;
	bool limitHit;
	PIDSource *pidInput;
	PIDOutput *pidOutput;
	DigitalInput *posLimit;
	DigitalInput *negLimit;

	CRITICAL_REGION(m_semaphore)
	{
		pidInput = m_pidInput;
		pidOutput = m_pidOutput;
		posLimit = m_posLimit;
		negLimit = m_negLimit;
		enabled = m_enabled;
		limitHit = m_limitHit;
		pidInput = m_pidInput;
	}
	END_REGION;

	if (pidInput == NULL) return;
	if (pidOutput == NULL) return;

	if (enabled)
	{
		{
			Synchronized sync(m_semaphore);
			float input = pidInput->PIDGet();
			float bumpAmt = 0;
			float result;
			PIDOutput *pidOutput;

			bool negLimitHit = false;
			bool posLimitHit = false;
			if (posLimit != NULL) posLimitHit = (limitHit == posLimit->Get());
			if (negLimit != NULL) negLimitHit = (limitHit == negLimit->Get());

			if ((posLimitHit && (m_targetSetpoint > input) ) || (negLimitHit && (m_targetSetpoint < input)))
			{
				m_targetSetpoint = input;
				m_setpoint = input;
				m_totalError = 0;
				m_prevError = 0;
			}

			if ((m_jogDir > 0 && posLimitHit) || (m_jogDir < 0 && negLimitHit))
			{
					m_jogDir = 0;
			}
			if (m_jogDir != 0)
			{
				m_targetSetpoint += (m_jogDir > 0) ? m_rate : -m_rate;
			}

			float inc = m_targetSetpoint - m_setpoint;
			if (m_continuous)
			{
				if (fabs(inc) > (m_maximumInput - m_minimumInput) / 2)
				{
					if (inc > 0)
					{
						inc = inc - m_maximumInput + m_minimumInput;
					}
					else
					{
						inc = inc + m_maximumInput - m_minimumInput;
					}
				}
			}

			if (fabs(inc) <= m_rate)
			{
				m_setpoint = m_targetSetpoint;
				bumpAmt = inc;
			}
			else
			{
				bumpAmt = (inc < 0) ? -m_rate : m_rate;
				m_setpoint += bumpAmt;
			}

			m_error = m_setpoint - input;
			if (m_continuous)
			{
				if (fabs(m_error) > (m_maximumInput - m_minimumInput) / 2)
				{
					if (m_error > 0)
					{
						m_error = m_error - m_maximumInput + m_minimumInput;
					}
					else
					{
						m_error = m_error + m_maximumInput - m_minimumInput;
					}
				}
			}

			if(m_I != 0)
			{
				double potentialIGain = (m_totalError + m_error - bumpAmt) * m_I;
				if (potentialIGain < m_maximumOutput)
				{
					if (potentialIGain > m_minimumOutput)
						m_totalError += m_error;
					else
						m_totalError = m_minimumOutput / m_I;
				}
				else
				{
					m_totalError = m_maximumOutput / m_I;
				}
				if ((m_targetSetpoint == m_setpoint) && (fabs(m_error) < m_autoReset))
				{
					m_totalError = 0;
				}
			}

			m_result = m_P * m_error + m_I * m_totalError + m_D * (m_error - m_prevError - bumpAmt) + m_setpoint * m_F + bumpAmt * m_V;
			if (m_result > 0 && posLimitHit) m_result = 0;
			if (m_result < 0 && negLimitHit) m_result = 0;
			m_prevError = m_error;

			if (m_result > m_maximumOutput) m_result = m_maximumOutput;
			else if (m_result < m_minimumOutput) m_result = m_minimumOutput;

			pidOutput = m_pidOutput;
			result = m_result;

			pidOutput->PIDWrite(result);
		}
	}
}

/**
 * Set the PID Controller gain parameters.
 * Set the proportional, integral, and differential coefficients.
 * @param p Proportional coefficient
 * @param i Integral coefficient
 * @param d Differential coefficient
 */
void AdvPIDController::SetPID(float p, float i, float d)
{
	CRITICAL_REGION(m_semaphore)
	{
		m_P = p;
		m_I = i;
		m_D = d;
	}
	END_REGION;

	if (m_table != NULL) {
		m_table->PutNumber("p", m_P);
		m_table->PutNumber("i", m_I);
		m_table->PutNumber("d", m_D);
	}
}

/**
 * Set the PID Controller gain parameters.
 * Set the proportional, integral, and differential coefficients.
 * @param p Proportional coefficient
 * @param i Integral coefficient
 * @param d Differential coefficient
 * @param f Feed forward coefficient
 */
void AdvPIDController::SetPID(float p, float i, float d, float f)
{
	CRITICAL_REGION(m_semaphore)
	{
		m_P = p;
		m_I = i;
		m_D = d;
		m_F = f;
	}
	END_REGION;

	if (m_table != NULL) {
		m_table->PutNumber("p", m_P);
		m_table->PutNumber("i", m_I);
		m_table->PutNumber("d", m_D);
		m_table->PutNumber("f", m_F);
	}
}

/**
 * Set the PID Controller gain parameters.
 * Set the proportional, integral, and differential coefficients.
 * @param p Proportional coefficient
 * @param i Integral coefficient
 * @param d Differential coefficient
 * @param f Feed forward coefficient
 */
void AdvPIDController::SetPID(float p, float i, float d, float f, float v)
{
	CRITICAL_REGION(m_semaphore)
	{
		m_P = p;
		m_I = i;
		m_D = d;
		m_F = f;
		m_V = v;
	}
	END_REGION;

	if (m_table != NULL) {
		m_table->PutNumber("p", m_P);
		m_table->PutNumber("i", m_I);
		m_table->PutNumber("d", m_D);
		m_table->PutNumber("f", m_F);
		m_table->PutNumber("v", m_V);
	}
}

/**
 * Get the Proportional coefficient
 * @return proportional coefficient
 */
float AdvPIDController::GetP()
{
	CRITICAL_REGION(m_semaphore)
	{
		return m_P;
	}
	END_REGION;
}

/**
 * Get the Integral coefficient
 * @return integral coefficient
 */
float AdvPIDController::GetI()
{
	CRITICAL_REGION(m_semaphore)
	{
		return m_I;
	}
	END_REGION;
}

/**
 * Get the Differential coefficient
 * @return differential coefficient
 */
float AdvPIDController::GetD()
{
	CRITICAL_REGION(m_semaphore)
	{
		return m_D;
	}
	END_REGION;
}

/**
 * Get the Feed forward coefficient
 * @return Feed forward coefficient
 */
float AdvPIDController::GetF()
{
	CRITICAL_REGION(m_semaphore)
	{
		return m_F;
	}
	END_REGION;
}

/**
 * Get the Feed forward coefficient
 * @return Feed forward coefficient
 */
float AdvPIDController::GetV()
{
	CRITICAL_REGION(m_semaphore)
	{
		return m_V;
	}
	END_REGION;
}

/**
 * Return the current PID result
 * This is always centered on zero and constrained the the max and min outs
 * @return the latest calculated output
 */
float AdvPIDController::Get()
{
	float result;
	CRITICAL_REGION(m_semaphore)
	{
		result = m_result;
	}
	END_REGION;
	return result;
}

/**
 *  Set the PID controller to consider the input to be continuous,
 *  Rather then using the max and min in as constraints, it considers them to
 *  be the same point and automatically calculates the shortest route to
 *  the setpoint.
 * @param continuous Set to true turns on continuous, false turns off continuous
 */
void AdvPIDController::SetContinuous(bool continuous)
{
	CRITICAL_REGION(m_semaphore)
	{
		m_continuous = continuous;
	}
	END_REGION;
}

/**
 * Sets the maximum and minimum values expected from the input.
 *
 * @param minimumInput the minimum value expected from the input
 * @param maximumInput the maximum value expected from the output
 */
void AdvPIDController::SetInputRange(float minimumInput, float maximumInput)
{
	CRITICAL_REGION(m_semaphore)
	{
		m_minimumInput = minimumInput;
		m_maximumInput = maximumInput;	
	}
	END_REGION;

	SetSetpoint(m_setpoint);
}

/**
 * Sets the minimum and maximum values to write.
 *
 * @param minimumOutput the minimum value to write to the output
 * @param maximumOutput the maximum value to write to the output
 */
void AdvPIDController::SetOutputRange(float minimumOutput, float maximumOutput)
{
	CRITICAL_REGION(m_semaphore)
	{
		m_minimumOutput = minimumOutput;
		m_maximumOutput = maximumOutput;
	}
	END_REGION;
}

/**
 * Set the setpoint for the AdvPIDController
 * @param setpoint the desired setpoint
 */
void AdvPIDController::SetSetpoint(float setpoint, float rate)
{
	CRITICAL_REGION(m_semaphore)
	{
		m_rate = rate;
		m_jogDir = 0;
		if (m_maximumInput > m_minimumInput)
		{
			if (setpoint > m_maximumInput)
				m_targetSetpoint = m_maximumInput;
			else if (setpoint < m_minimumInput)
				m_targetSetpoint = m_minimumInput;
			else
				m_targetSetpoint = setpoint;
		}
		else
		{
			m_targetSetpoint = setpoint;
		}
	}
	END_REGION;	
	
	if (m_table != NULL) {
		m_table->PutNumber("setpoint", m_setpoint);
	}
}
/**
 * Jog PID in direction at given rate
 * @param rate desired jog rate per period
 */
void AdvPIDController::SetJog(float rate)
{
	CRITICAL_REGION(m_semaphore)
	{
		m_rate = fabs(rate);
		m_jogDir = (rate > 0) ? 1 : ((rate < 0) ? -1 : 0);
	}
	END_REGION;

	if (m_table != NULL) {
		m_table->PutNumber("setpoint", m_setpoint);
	}
}
/**
 * Disable PID Jogging
 */
void AdvPIDController::DisableJog()
{
	CRITICAL_REGION(m_semaphore)
	{
		m_jogDir = 0;
	}
	END_REGION;

	if (m_table != NULL) {
		m_table->PutNumber("setpoint", m_setpoint);
	}
}
/**
 * Get current PID Jog Direction
 * 0 is Jog stopped/disabled
 */
int AdvPIDController::GetJogDir()
{
	int jogDir;
	CRITICAL_REGION(m_semaphore)
	{
		jogDir = m_jogDir;
	}
	END_REGION;
	return jogDir;
}

/**
 * Sets Auto reset amount, which resets I error when stationary and error < resetErr
 * Useful for "sticky" systems to use I to reduce error, then reset so motors don't
 * keep drawing current.
 * @param resetErr Error amount at which to reset accumulated error.
 */
void AdvPIDController::SetAutoReset(float resetErr)
{
	CRITICAL_REGION(m_semaphore)
	{
		m_autoReset = fabs(resetErr);
	}
	END_REGION;
}

/**
 * Get Auto I Reset value
 */
float AdvPIDController::GetAutoReset()
{
	float resetErr;
	CRITICAL_REGION(m_semaphore)
	{
		resetErr = m_autoReset;
	}
	END_REGION;
	return resetErr;
}

/**
 * Returns the current setpoint of the AdvPIDController
 * @return the current setpoint
 */
float AdvPIDController::GetSetpoint()
{
	float setpoint;
	CRITICAL_REGION(m_semaphore)
	{
		setpoint = m_targetSetpoint;
	}
	END_REGION;
	return setpoint;
}

/**
 * Retruns the current difference of the input from the setpoint
 * @return the current error
 */
float AdvPIDController::GetError()
{
	float error;
  double pidInput;
    float setpoint;
	CRITICAL_REGION(m_semaphore)
	{
    pidInput = m_pidInput->PIDGet();
    setpoint = m_setpoint;
	}
	END_REGION;
  error = setpoint - pidInput;
	return error;
}

/*
 * Set the percentage error which is considered tolerable for use with
 * OnTarget.
 * @param percentage error which is tolerable
 */
void AdvPIDController::SetTolerance(float percent)
{
	CRITICAL_REGION(m_semaphore)
	{
		m_toleranceType = kPercentTolerance;
		m_tolerance = percent;
	}
	END_REGION;
}

/*
 * Set the percentage error which is considered tolerable for use with
 * OnTarget.
 * @param percentage error which is tolerable
 */
void AdvPIDController::SetPercentTolerance(float percent)
{
	CRITICAL_REGION(m_semaphore)
	{
		m_toleranceType = kPercentTolerance;
		m_tolerance = percent;
	}
	END_REGION;
}

/*
 * Set the absolute error which is considered tolerable for use with
 * OnTarget.
 * @param percentage error which is tolerable
 */
void AdvPIDController::SetAbsoluteTolerance(float absTolerance)
{
	CRITICAL_REGION(m_semaphore)
	{
		m_toleranceType = kAbsoluteTolerance;
		m_tolerance = absTolerance;
	}
	END_REGION;
}

/*
 * Return true if the error is within the percentage of the total input range,
 * determined by SetTolerance. This asssumes that the maximum and minimum input
 * were set using SetInput.
 * Currently this just reports on target as the actual value passes through the setpoint.
 * Ideally it should be based on being within the tolerance for some period of time.
 */
bool AdvPIDController::OnTarget()
{
	bool temp;
  double error = GetError();
	CRITICAL_REGION(m_semaphore)
	{
		if (m_targetSetpoint == m_setpoint)
		{
			switch (m_toleranceType) {
			case kPercentTolerance:
				temp = fabs(error) < (m_tolerance / 100 * (m_maximumInput - m_minimumInput));
				break;
			case kAbsoluteTolerance:
				temp = fabs(error) < m_tolerance;
				break;
			//TODO: this case needs an error
			case kNoTolerance:
				temp = false;
			}
		} else
		{
			temp = false;
		}
	}
	END_REGION;
	return temp;
}

/**
 * Begin running the AdvPIDController
 */
void AdvPIDController::Enable()
{

	PIDSource *pidInput;

	CRITICAL_REGION(m_semaphore)
	{			
		pidInput = m_pidInput;
		m_enabled = true;
		if (pidInput != NULL)
		{
			float input = pidInput->PIDGet();
			m_targetSetpoint = input;
			m_setpoint = input;
		}
		m_jogDir = 0;
	}
	END_REGION;	
	
	if (m_table != NULL) {
		m_table->PutBoolean("enabled", true);
	}

}

/**
 * Stop running the AdvPIDController, this sets the output to zero before stopping.
 */
void AdvPIDController::Disable()
{
	CRITICAL_REGION(m_semaphore)
	{
		m_pidOutput->PIDWrite(0);
		m_enabled = false;
		m_jogDir = 0;
	}
	END_REGION;
	
	if (m_table != NULL) {
		m_table->PutBoolean("enabled", false);
	}
}

/**
 * Return true if AdvPIDController is enabled.
 */
bool AdvPIDController::IsEnabled()
{
	bool enabled;
	CRITICAL_REGION(m_semaphore)
	{
		enabled = m_enabled;
	}
	END_REGION;
	return enabled;
}

/**
 * Reset the previous error,, the integral term, and disable the controller.
 */
void AdvPIDController::Reset()
{
	Disable();

	CRITICAL_REGION(m_semaphore)
	{
		m_prevError = 0;
		m_totalError = 0;
		m_result = 0;
	}
	END_REGION;
}

std::string AdvPIDController::GetSmartDashboardType(){
	return "AdvPIDController";
}

void AdvPIDController::InitTable(ITable* table){
	if(m_table!=NULL)
		m_table->RemoveTableListener(this);
	m_table = table;
	if(m_table!=NULL){
		m_table->PutNumber(kP, GetP());
		m_table->PutNumber(kI, GetI());
		m_table->PutNumber(kD, GetD());
		m_table->PutNumber(kF, GetF());
		m_table->PutNumber(kV, GetV());
		m_table->PutNumber(kSetpoint, GetSetpoint());
		m_table->PutBoolean(kEnabled, IsEnabled());
		m_table->AddTableListener(this, false);
	}
}

ITable* AdvPIDController::GetTable(){
	return m_table;
}

void AdvPIDController::ValueChanged(ITable* source, const std::string& key, EntryValue value, bool isNew){
	if (key==kP || key==kI || key==kD || key==kF) {
		if (m_P != m_table->GetNumber(kP) || m_I != m_table->GetNumber(kI) || m_D != m_table->GetNumber(kD) || m_F != m_table->GetNumber(kF)  ) {
			SetPID(m_table->GetNumber(kP, 0.0), m_table->GetNumber(kI, 0.0), m_table->GetNumber(kD, 0.0), m_table->GetNumber(kF, 0.0));
		}
	} else if (key==kSetpoint && m_setpoint != value.f) {
		SetSetpoint(value.f);
	} else if (key==kEnabled && m_enabled != value.b) {
		if (value.b) {
			Enable();
		} else {
			Disable();
		}
	}
}

void AdvPIDController::UpdateTable() {

}

void AdvPIDController::StartLiveWindowMode() {
	Disable();
}

void AdvPIDController::StopLiveWindowMode() {

}
