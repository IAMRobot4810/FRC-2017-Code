/*
 * GearPickup.h
 *
 *  Created on: Feb 11, 2017
 *      Author: Anish
 */

#ifndef SRC_SYSTEMS_GEARPICKUP_H_
#define SRC_SYSTEMS_GEARPICKUP_H_
#include "WPILib.h"
#include "util/DeviceIDs.h"
#include "systems/Constants.h"
using namespace frc;

class GearPickup {
public:
	GearPickup(XboxController* controller);
	virtual ~GearPickup();
	DoubleSolenoid* liftSolenoid;
	DoubleSolenoid* clampSolenoid;
	XboxController* controller;
	DigitalInput* banner;
	void teleopGearLoop();
	void teleopGearLoopMod();
	bool liftSolenoidToggle = true;
	bool clampSolenoidToggle = true;
	void teleopGearLoopMod2();
	void teleopGearLoopSensor();
	bool getIsGear();
	bool clawControl = false;
};

#endif /* SRC_SYSTEMS_GEARPICKUP_H_ */
