/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2011. All Rights Reserved.							  */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
/*----------------------------------------------------------------------------*/

#ifndef __ADVPID_SUBSYSTEM_H__
#define __ADVPID_SUBSYSTEM_H__

#include "Commands/Subsystem.h"
#include "AdvPIDController.h"
#include "PIDSource.h"
#include "PIDOutput.h"

/**
 * This class is designed to handle the case where there is a {@link Subsystem}
 * which uses a single {@link AdvPIDController} almost constantly (for instance, 
 * an elevator which attempts to stay at a constant height).
 *
 * <p>It provides some convenience methods to run an internal {@link AdvPIDController}.
 * It also allows access to the internal {@link AdvPIDController} in order to give total control
 * to the programmer.</p>
 *
 */
class AdvPIDSubsystem : public Subsystem, public PIDOutput, public PIDSource
{
public:
	AdvPIDSubsystem(const char *name, double p, double i, double d);
	AdvPIDSubsystem(const char *name, double p, double i, double d, double f);
	AdvPIDSubsystem(const char *name, double p, double i, double d, double f, double period);
	AdvPIDSubsystem(double p, double i, double d);
	AdvPIDSubsystem(double p, double i, double d, double f);
	AdvPIDSubsystem(double p, double i, double d, double f, double period);
	virtual ~AdvPIDSubsystem();
	
	void Enable();
	void Disable();

	// PIDOutput interface
	virtual void PIDWrite(float output);

	// PIDSource interface
	virtual double PIDGet();
	void SetSetpoint(double setpoint);
	void SetSetpointRelative(double deltaSetpoint);
	void SetInputRange(float minimumInput, float maximumInput);
	double GetSetpoint();
	double GetPosition();

	virtual void SetAbsoluteTolerance(float absValue);
	virtual void SetPercentTolerance(float percent);
	virtual bool OnTarget();
	
protected:
	AdvPIDController *GetPIDController();

	virtual double ReturnPIDInput() = 0;
	virtual void UsePIDOutput(double output) = 0;

private:
	/** The internal {@link AdvPIDController} */
	AdvPIDController *m_controller;

public:
	virtual void InitTable(ITable* table);
	virtual std::string GetSmartDashboardType();
};

#endif

