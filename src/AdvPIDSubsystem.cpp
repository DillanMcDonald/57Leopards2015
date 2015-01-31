/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2011. All Rights Reserved.							  */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
/*----------------------------------------------------------------------------*/

#include "AdvPIDSubsystem.h"
#include "AdvPIDController.h"
#include "float.h"

// XXX max and min are not used?

/**
 * Instantiates a {@link AdvPIDSubsystem} that will use the given p, i and d values.
 * @param name the name
 * @param p the proportional value
 * @param i the integral value
 * @param d the derivative value
 */
AdvPIDSubsystem::AdvPIDSubsystem(const char *name, double p, double i, double d) :
	Subsystem(name)
{
	m_controller = new AdvPIDController(p, i, d, this, this);
}

/**
 * Instantiates a {@link AdvPIDSubsystem} that will use the given p, i and d values.
 * @param name the name
 * @param p the proportional value
 * @param i the integral value
 * @param d the derivative value
 * @param f the feedforward value
 */
AdvPIDSubsystem::AdvPIDSubsystem(const char *name, double p, double i, double d, double f) :
	Subsystem(name)
{
	m_controller = new AdvPIDController(p, i, d, f, this, this);
}

/**
 * Instantiates a {@link AdvPIDSubsystem} that will use the given p, i and d values.  It will also space the time
 * between PID loop calculations to be equal to the given period.
 * @param name the name
 * @param p the proportional value
 * @param i the integral value
 * @param d the derivative value
 * @param f the feedfoward value
 * @param period the time (in seconds) between calculations
 */
AdvPIDSubsystem::AdvPIDSubsystem(const char *name, double p, double i, double d, double f,
	double period) :
	Subsystem(name)
{
	m_controller = new AdvPIDController(p, i, d, f, this, this, period);
}

/**
 * Instantiates a {@link AdvPIDSubsystem} that will use the given p, i and d values.
 * It will use the class name as its name.
 * @param p the proportional value
 * @param i the integral value
 * @param d the derivative value
 */
AdvPIDSubsystem::AdvPIDSubsystem(double p, double i, double d) :
	Subsystem("AdvPIDSubsystem")
{
	m_controller = new AdvPIDController(p, i, d, this, this);
}

/**
 * Instantiates a {@link AdvPIDSubsystem} that will use the given p, i and d values.
 * It will use the class name as its name.
 * @param p the proportional value
 * @param i the integral value
 * @param d the derivative value
 * @param f the feedforward value
 */
AdvPIDSubsystem::AdvPIDSubsystem(double p, double i, double d, double f) :
	Subsystem("AdvPIDSubsystem")
{
	m_controller = new AdvPIDController(p, i, d, f, this, this);
}

/**
 * Instantiates a {@link AdvPIDSubsystem} that will use the given p, i and d values.
 * It will use the class name as its name.
 * It will also space the time
 * between PID loop calculations to be equal to the given period.
 * @param p the proportional value
 * @param i the integral value
 * @param d the derivative value
 * @param f the feedforward value
 * @param period the time (in seconds) between calculations
 */
AdvPIDSubsystem::AdvPIDSubsystem(double p, double i, double d, double f, double period) :
	Subsystem("AdvPIDSubsystem")
{
	m_controller = new AdvPIDController(p, i, d, f, this, this, period);
}

AdvPIDSubsystem::~AdvPIDSubsystem()
{
	delete m_controller;
}

/**
 * Enables the internal {@link AdvPIDController}
 */
void AdvPIDSubsystem::Enable()
{
	m_controller->Enable();
}

/** 
  * Disables the internal {@link AdvPIDController}
  */
void AdvPIDSubsystem::Disable()
{
	m_controller->Disable();
}


/**
 * Returns the {@link AdvPIDController} used by this {@link AdvPIDSubsystem}.
 * Use this if you would like to fine tune the pid loop.
 *
 * @return the {@link AdvPIDController} used by this {@link AdvPIDSubsystem}
 */
AdvPIDController *AdvPIDSubsystem::GetPIDController()
{
	return m_controller;
}

/**
 * Sets the setpoint to the given value.  If {@link PIDCommand#SetRange(double, double) SetRange(...)}
 * was called,
 * then the given setpoint
 * will be trimmed to fit within the range.
 * @param setpoint the new setpoint
 */
void AdvPIDSubsystem::SetSetpoint(double setpoint)
{
	m_controller->SetSetpoint(setpoint);
}

/**
 * Adds the given value to the setpoint.
 * If {@link PIDCommand#SetRange(double, double) SetRange(...)} was used,
 * then the bounds will still be honored by this method.
 * @param deltaSetpoint the change in the setpoint
 */
void AdvPIDSubsystem::SetSetpointRelative(double deltaSetpoint)
{
	SetSetpoint(GetSetpoint() + deltaSetpoint);
}

/**
 * Return the current setpoint
 * @return The current setpoint
 */
double AdvPIDSubsystem::GetSetpoint()
{
	return m_controller->GetSetpoint();
}

/**
 * Sets the maximum and minimum values expected from the input.
 * 
 * @param minimumInput the minimum value expected from the input
 * @param maximumInput the maximum value expected from the output
 */
void AdvPIDSubsystem::SetInputRange(float minimumInput, float maximumInput)
{
	m_controller->SetInputRange(minimumInput, maximumInput);
}

/*
 * Set the absolute error which is considered tolerable for use with
 * OnTarget.
 * @param percentage error which is tolerable
 */
void AdvPIDSubsystem::SetAbsoluteTolerance(float absValue) {
	m_controller->SetAbsoluteTolerance(absValue);
}

/*
 * Set the percentage error which is considered tolerable for use with
 * OnTarget.
 * @param percentage error which is tolerable
 */
void AdvPIDSubsystem::SetPercentTolerance(float percent) {
	m_controller->SetPercentTolerance(percent);
}

/*
 * Return true if the error is within the percentage of the total input range,
 * determined by SetTolerance. This asssumes that the maximum and minimum input
 * were set using SetInput. Use OnTarget() in the IsFinished() method of commands
 * that use this subsystem.
 * 
 * Currently this just reports on target as the actual value passes through the setpoint.
 * Ideally it should be based on being within the tolerance for some period of time.
 * 
 * @return true if the error is within the percentage tolerance of the input range
 */
bool AdvPIDSubsystem::OnTarget()
{
	return m_controller->OnTarget();
}

/**
 * Returns the current position
 * @return the current position
 */
double AdvPIDSubsystem::GetPosition()
{
	return ReturnPIDInput();
}

void AdvPIDSubsystem::PIDWrite(float output)
{
	UsePIDOutput(output);
}

double AdvPIDSubsystem::PIDGet()
{
	return ReturnPIDInput();
}


std::string AdvPIDSubsystem::GetSmartDashboardType(){
	return "PIDCommand";
}
void AdvPIDSubsystem::InitTable(ITable* table){
	m_controller->InitTable(table);
	Subsystem::InitTable(table);
}
