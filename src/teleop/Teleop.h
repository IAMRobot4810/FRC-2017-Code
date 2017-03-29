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
#include <systems/ShootSystem/ShootSystem.h>

class Teleop {

public:
	Teleop(XboxController* controller1, XboxController* controller2, DriveSystem* driveSystem,
			GearSystem* gearSystem, DigitalInput* gearDetectSensor, DigitalInput* pegDetectSensor1,
			DigitalInput* pegDetectSensor2, ClimbSystem* climbSystem, ShootSystem* shootSystem);
	~Teleop();

	enum teleopMode{
		OneContNoSensors = 0,
		TwoContNoSensors = 1,
		OneContSensors = 2,
		TwoContSensors = 3
	};

	void TeleopRun(teleopMode teleMode);

private:
	DriveSystem* drv;
	GearSystem* gr;
	XboxController* cont1;
	XboxController* cont2;
	Deadband* dBand;
	Scaler* scale;
	DigitalInput* gDetect;
	DigitalInput* pDetect1;
	DigitalInput* pDetect2;
	ClimbSystem* clb;
	ShootSystem* sht;

	bool a1Toggle;
	bool a2Toggle;
	bool b2Toggle;
	bool y2Toggle;
	bool l1BumpToggle;
	bool r1BumpToggle;
	bool l2BumpToggle;
	bool r2BumpToggle;
	bool manualClaw;

protected:

};

#endif
