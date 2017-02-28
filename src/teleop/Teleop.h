/*
 * Teleop.hpp
 *
 *  Created on: Feb 11, 2017
 *      Author: 4810
 */
#ifndef SRC_UTIL_TELEOP_H_
#define SRC_UTIL_TELEOP_H_

#include <util/DeviceID.h>
#include <systems/DriveSystem/DriveSystem.h>
#include <systems/GearSystem/GearSystem.h>
#include <util/Scaler.h>
#include <teleop/controls/Deadband.h>
#include <util/ConstantVals.h>
#include <XboxController.h>
#include <SmartDashboard/SmartDashboard.h>
#include <systems/ClimbSystem/ClimbSystem.h>
#include <Systems/BallSystem/BallSystem.h>

class Teleop {

public:
	Teleop(XboxController* controller1, XboxController* controller2, DriveSystem* driveSystem,
			GearSystem* gearSystem, DigitalInput* gearDetectSensor, DigitalInput* pegDetectSensor,
			ClimbSystem* climbSystem, BallSystem* ballSystem);
	~Teleop();

	void TeleopRun(bool sensors);

private:
	DriveSystem* drv;
	GearSystem* gr;
	XboxController* cont1;
	XboxController* cont2;
	Deadband* dBand;
	Scaler* scale;
	DigitalInput* gDetect;
	DigitalInput* pDetect;
	ClimbSystem* clb;
	BallSystem* bll;

	bool a1Toggle;
	bool b1Toggle;
	bool y1Toggle;
	bool lBumpToggle;
	bool rBumpToggle;
	bool manualClaw;

protected:

};

#endif
