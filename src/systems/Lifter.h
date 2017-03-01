/*
 * Lifter.h
 *
 *  Created on: Feb 17, 2017
 *      Author: Anish
 */

#ifndef SRC_SYSTEMS_LIFTER_H_
#define SRC_SYSTEMS_LIFTER_H_

#include "WPILib.h"
#include "CANTalon.h"
#include "teleop/controls/Deadband.h"
#include "util/DeviceIDs.h"
#include "systems/Constants.h"
using namespace frc;

class Lifter {
public:
	Lifter(XboxController* controller);
	virtual ~Lifter();
	void TeleopLoop();
	void TeleopLoopImproved();
	CANTalon* leftInRoller;
	CANTalon* rightInRoller;
	CANTalon* liftTalon;
	XboxController* controller;
};

#endif /* SRC_SYSTEMS_LIFTER_H_ */
