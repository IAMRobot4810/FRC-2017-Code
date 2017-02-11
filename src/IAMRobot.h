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
using namespace frc;
class IAMRobot: public IterativeRobot {

public:
	IAMRobot();
	~IAMRobot();

private:
	XboxController *mainController;
	CANTalon *flTalon;
	CANTalon *frTalon;
	CANTalon *rlTalon;
	CANTalon *rrTalon;
	RobotDrive *drive;
	Encoder* driveEncoder1;
	Encoder* driveEncoder2;

	int driveEncoder1Port1;
	int driveEncoder1Port2;
	int driveEncoder2Port1;
	int driveEncoder2Port2;
	int flTalID = 1;
	int frTalID = 3;
	int rlTalID = 2;
	int rrTalID = 4;
	int mainControllerID = 0;

	void RobotInit() override;
	void AutonomousInit() override;
	void AutonomousPeriodic() override;
	void TeleopInit() override;
	void TeleopPeriodic() override;
	void TestPeriodic() override;

};

#endif /* SRC_IAMROBOT_H_ */
