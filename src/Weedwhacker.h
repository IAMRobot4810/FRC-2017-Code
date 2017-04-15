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
	ADXRS450_Gyro* gyration;
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
	LiveWindow *lw = LiveWindow::GetInstance();

	bool gearAuto;
	int shootAutoPower;
	Auto::AutoPosition gearPosEnum;
	Auto::shooterPowMode shootPowerEnum;
	bool gearFirst;

protected:

};

#endif /* SRC_WEEDWHACKER_H_ */
