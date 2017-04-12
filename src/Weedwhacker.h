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

//Header guards
#ifndef SRC_WEEDWHACKER_H_
#define SRC_WEEDWHACKER_H_

//Standard C++ includes
#include <iostream>
#include <memory>
#include <string>

//WPILib includes
#include <IterativeRobot.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>
#include <WPILib.h>

//Weedwhacker includes
#include <util/ConstantVals.h>
#include <teleop/Teleop.h>
#include <auto/Auto.h>
#include <Relay.h>
#include <PowerDistributionPanel.h>

using namespace frc;

class Weedwhacker: public frc::IterativeRobot { // Overall robot class

public:
	Weedwhacker(); //Constructor
	~Weedwhacker(); //Destructor

	//DriveSystem objects
	CANTalon* flTalon;
	CANTalon* rlTalon;
	CANTalon* frTalon;
	CANTalon* rrTalon;
	RobotDrive* robotDrive;
	AnalogGyro* gyration;
	DriveSystem* drive;

	//GearSystem objects
	DoubleSolenoid* gearClawNoid;
	DoubleSolenoid* gearRaiseNoid;
	GearSystem* gear;
	DigitalInput* gearSensor;
	DigitalInput* pegSensor; //*NEEDS TESTING*

	//ClimbSystem objects
	CANTalon* climb1Roller;
	CANTalon* climb2Roller;
	ClimbSystem* climb;

	//ShootSystem objects
	CANTalon* feedingTal;
	CANTalon* meteringTal;
	CANTalon* shooterTal;
	ShootSystem* ball;

	//Teleop objects
	XboxController* control1;
	XboxController* control2;
	Teleop* tlp;

	//Autonomous objects
	Auto* ato;

	//Sight Cameras
	CameraServer* cammy;
	CameraServer* cammy2;

	//Status indicator/decoration LEDs
	Relay* rLED;
	Relay* gLED;
	Relay* bLED;

	void RobotInit(); //Initializes robot, runs at startup
	void AutonomousInit() override; //Runs once when autonomous is enabled
	void AutonomousPeriodic(); //Autonomous loop
	void TeleopInit(); //Runs once when teleop is enabled
	void TeleopPeriodic(); //Teleop loop
	void TestInit(); //Runs once when test mode is enabled, for testing
	void TestPeriodic(); //Test mode loop, for testing
	void DisabledInit(); //Runs once when robot is disabled
	void DisabledPeriodic(); //Disabled mode loop

private:
	//Autonomous modes chooser *NEEDS TESTING*
	LiveWindow *lw = LiveWindow::GetInstance();
	SendableChooser<std::string> autoChooser;
	const std::string autoNameDefault = "Default";
	const std::string autoNameMGear = "Middle Gear Auto";
	const std::string autoNameLBall = "Low Speed Ball Auto";
	const std::string autoNameMBall = "Medium Speed Ball Auto";
	const std::string autoNameHBall = "High Speed Ball Auto";
	const std::string autoNameMBallGear = "Middle BallGear Auto";
	const std::string autoNameMGearBall = "Middle GearBall Auto";
	std::string autoSelected;

	//Teleop modes chooser *NEEDS TESTING*
	SendableChooser<std::string> teleChooser;
	const std::string teleNameDefault = "2 Controller with Sensors";
	const std::string teleName1s = "1 Controller with Sensors";
	const std::string teleName1ns = "1 Controller with no Sensors";
	const std::string teleName2ns = "2 Controller with no Sensors";
	std::string teleSelected;

protected:

};

#endif /* SRC_WEEDWHACKER_H_ */
