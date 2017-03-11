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
	auxController = new XboxController(auxID);
	driveSystem = new DriveSystem(mainController);
	pickup = new GearPickup(mainController);
	baller = new Ball_Pickup(auxController);
	lifter = new Lifter(auxController);
	rLED = new Relay(rLEDID);
	bLED = new Relay(bLEDID);
	gLED = new Relay(gLEDID);

}

IAMRobot::~IAMRobot() {
	delete mainController;
	delete auxController;
	delete driveSystem;
	delete pickup;
	delete baller;
	delete lifter;
	delete rLED;
	delete bLED;
	delete gLED;
}
void IAMRobot::DisableInit(){

}
void IAMRobot::RobotInit(){
	CameraServer::GetInstance()->StartAutomaticCapture(0);
}
void IAMRobot::AutonomousInit(){

}
void IAMRobot::AutonomousPeriodic(){

}
void IAMRobot::TeleopInit(){

}
void IAMRobot::TeleopPeriodic(){
	driveSystem->ArcadeDriveStickSquare();
	pickup->teleopGearLoopMod();
	baller->TeleopBallLoop();
	lifter->TeleopLoop();

	if(pickup->getIsGear()){
		bLED->Set(Relay::Value::kForward);
		rLED->Set(Relay::Value::kOff);
	}else{
		bLED->Set(Relay::Value::kOff);
		rLED->Set(Relay::Value::kForward);
	}
}
void IAMRobot::TestPeriodic(){

}

START_ROBOT_CLASS(IAMRobot)
