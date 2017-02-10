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
using namespace frc;
class IAMRobot: public IterativeRobot {

public:
	IAMRobot();
	virtual ~IAMRobot();
private:
	CANTalon *flTalon;
	CANTalon *frTalon;
	CANTalon *blTalon;
	CANTalon *brTalon;
	RobotDrive *drive;
	Encoder* driveEncoder1;
	Encoder* driveEncoder2;
	int driveEncoder1Port1;
	int driveEncoder1Port2;
	int driveEncoder2Port1;
	int driveEncoder2Port2;
	int flTalID;
	int frTalID;
	int blTalID;
	int brTalID;
	int mainStickID;
	frc::Joystick *mainStick;
	void RobotInit();
	void AutonomousInit();
	void AutonomousPeriodic();
	void TeleopInit();
	void TeleopPeriodic();
	void TestPeriodic();

};

#endif /* SRC_IAMROBOT_H_ */
