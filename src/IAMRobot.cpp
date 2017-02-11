/*
 * IAMRobot.cpp
 *
 *  Created on: Feb 9, 2017
 *      Author: Anish
 */

#include <IAMRobot.h>
using namespace frc;
IAMRobot::IAMRobot() {

	flTalon = new CANTalon(flTalID);
	frTalon = new CANTalon(frTalID);
	rlTalon = new CANTalon(rlTalID);
	rrTalon = new CANTalon(rrTalID);
	drive  = new RobotDrive(flTalon,rlTalon,frTalon,rrTalon);
	mainController = new XboxController(mainControllerID);
	driveEncoder1 = new Encoder(driveEncoder1Port1,driveEncoder1Port2,true,Encoder::EncodingType::k4X);
	driveEncoder2 = new Encoder(driveEncoder2Port1,driveEncoder2Port2,true,Encoder::EncodingType::k4X);
}

IAMRobot::~IAMRobot() {
	delete drive;
	delete mainController;
	delete flTalon;
	delete frTalon;
	delete rlTalon;
	delete rrTalon;
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
	drive->ArcadeDrive(mainController->GetY(Joystick::kLeftHand),mainController->GetX(Joystick::kRightHand),false);
	SmartDashboard::PutNumber("Encoder1 Get:", driveEncoder1->Get());
	SmartDashboard::PutNumber("Encoder2 Get:", driveEncoder2->Get());
}
void IAMRobot::TestPeriodic(){

}

START_ROBOT_CLASS(IAMRobot)
