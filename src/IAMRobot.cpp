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
}

IAMRobot::~IAMRobot() {
	delete mainController;
	delete driveSystem;
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
	driveSystem->TankDriveStickSquare();
}
void IAMRobot::TestPeriodic(){

}

START_ROBOT_CLASS(IAMRobot)
