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
	bool isliftSolenoid = true;
	bool isclampSolenoid = true;
	bool yButtonPressed = false;
	bool xButtonPressed = false;
	void teleopGearLoopMod2();

};

#endif /* SRC_SYSTEMS_GEARPICKUP_H_ */
