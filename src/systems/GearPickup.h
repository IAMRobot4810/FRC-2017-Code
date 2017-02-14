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
using namespace frc;

class GearPickup {
public:
	GearPickup(XboxController* controller);
	virtual ~GearPickup();
	Solenoid* liftSolenoid;
	Solenoid* clampSolenoid;
	XboxController* controller;
	void teleopGearLoop();
	bool isliftSolenoid = true;
	bool isclampSolenoid = true;
	bool yButtonPressed = false;
	bool xButtonPressed = false;

};

#endif /* SRC_SYSTEMS_GEARPICKUP_H_ */
