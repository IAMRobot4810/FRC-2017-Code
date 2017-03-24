/*
 * IAMRobot.h
 *
 *  Created on: Feb 10, 2017
 *      Author: 4810
 *
 * Here we go robot. Do the thing. Throw the ball. Climb the rope. Put the gear in the slot on the peg.
 * Now the robot is fully programmed and it has developed a form of artificial intelligence. And martial arts.
 * The robot is self aware. Run.
 */

#ifndef SRC_IAMROBOT_H_
#define SRC_IAMROBOT_H_

#include <iostream>
#include <memory>
#include <string>

#include <IterativeRobot.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>
#include <WPILib.h>
#include <teleop/Teleop.h>
#include <auto/Auto.h>
#include <Relay.h>

using namespace frc;

class IAMRobot: public frc::IterativeRobot {

public:
	IAMRobot();
	~IAMRobot();

	CANTalon* flTalon;
	CANTalon* rlTalon;
	CANTalon* frTalon;
	CANTalon* rrTalon;
	RobotDrive* robotDrive;
	PWM* flEncoder;
	PWM* frEncoder;
	DriveSystem* drive;
	DoubleSolenoid* gearClawNoid;
	DoubleSolenoid* gearRaiseNoid;
	GearSystem* gear;
	CANTalon* climbRoller;
	CANTalon* climbLeft;
	CANTalon* climbRight;
	ClimbSystem* climb;
	CANTalon* ballWall1Tal;
	CANTalon* ballWall2Tal;
	DoubleSolenoid* pickupSol;
	BallSystem* ball;
	XboxController* control1;
	XboxController* control2;
	Teleop* tlp;
	Auto* ato;
	DigitalInput* gearSensor;
	DigitalInput* pegSensor1;
	DigitalInput* pegSensor2;
	CameraServer* cammy;
	Relay* rLED;
	Relay* gLED;
	Relay* bLED;

	void RobotInit();
	void AutonomousInit() override;
	void AutonomousPeriodic();
	void TeleopInit();
	void TeleopPeriodic();
	void TestPeriodic();
	void DisabledInit();
	void DisabledPeriodic();

private:
	LiveWindow *lw = LiveWindow::GetInstance();
	SendableChooser<std::string> autoChooser;
	const std::string autoNameDefault = "Default";
	const std::string autoNameCustom = "Gear Auto";
	std::string autoSelected;

	SendableChooser<std::string> teleChooser;
	const std::string teleNameDefault = "2 Controller with Sensors";
	const std::string teleName1s = "1 Controller with Sensors";
	const std::string teleName1ns = "1 Controller with no Sensors";
	const std::string teleName2ns = "2 Controller with no Sensors";
	std::string teleSelected;

protected:

};

#endif /* SRC_IAMROBOT_H_ */
