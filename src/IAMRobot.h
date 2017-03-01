/*
 * IAMRobot.h
 *
 *  Created on: Feb 9, 2017
 *      Author: Anish
 */

#ifndef SRC_IAMROBOT_H_
#define SRC_IAMROBOT_H_
#include "WPILib.h"
#include "CANTalon.h"
#include <iostream>
#include <memory>
#include <string>

#include <IterativeRobot.h>
#include "systems/DriveSystem.h"
#include "util/DeviceIDs.h"
#include "systems/GearPickup.h"
#include "systems/BallPickup.h"
#include "systems/Lifter.h"
using namespace frc;

class IAMRobot: public IterativeRobot {

public:
	IAMRobot();
	~IAMRobot();

private:
	XboxController *mainController;
	DriveSystem* driveSystem;
	GearPickup* pickup;
	Ball_Pickup* baller;
	Lifter* lifter;
	void RobotInit() override;
	void AutonomousInit() override;
	void AutonomousPeriodic() override;
	void TeleopInit() override;
	void TeleopPeriodic() override;
	void TestPeriodic() override;

};

#endif /* SRC_IAMROBOT_H_ */
