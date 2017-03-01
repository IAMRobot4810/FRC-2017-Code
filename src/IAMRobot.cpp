/*
 * IAMRobot.cpp
 *
 *  Created on: Feb 9, 2017
 *      Author: Anish
 */

#include <IAMRobot.h>
using namespace frc;

IAMRobot::IAMRobot() {
	mainController = new XboxController(mainControllerID);
	driveSystem = new DriveSystem(mainController);
	pickup = new GearPickup(mainController);
	baller = new Ball_Pickup(mainController);
	lifter = new Lifter(mainController);
}

IAMRobot::~IAMRobot() {
	delete mainController;
	delete driveSystem;
	delete pickup;
	delete baller;
	delete lifter;
}

void IAMRobot::RobotInit(){

}
void IAMRobot::AutonomousInit(){

}
void IAMRobot::AutonomousPeriodic(){

}
void IAMRobot::TeleopInit(){

}
void IAMRobot::TeleopPeriodic(){
	driveSystem->ArcadeDriveStickSquare();
	pickup->teleopGearLoop();
	baller->TeleopBallLoop();
	lifter->TeleopLoop();
}
void IAMRobot::TestPeriodic(){

}

START_ROBOT_CLASS(IAMRobot)
