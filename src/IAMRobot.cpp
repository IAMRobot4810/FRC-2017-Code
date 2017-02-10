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
	blTalon = new CANTalon(blTalID);
	brTalon = new CANTalon(brTalID);
	drive  = new RobotDrive(flTalon,frTalon,blTalon,brTalon);
	mainStick = new Joystick(mainStickID);
	driveEncoder1 = new Encoder(driveEncoder1Port1,driveEncoder1Port2,true,Encoder::EncodingType::k4X);
	driveEncoder2 = new Encoder(driveEncoder2Port1,driveEncoder2Port2,true,Encoder::EncodingType::k4X);
}

IAMRobot::~IAMRobot() {
	delete drive;
	delete mainStick;
	delete flTalon;
	delete frTalon;
	delete blTalon;
	delete brTalon;
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
	drive->ArcadeDrive(mainStick);
	SmartDashboard::PutNumber("Encoder1 Rate:", driveEncoder1->Get());
	SmartDashboard::PutNumber("Encoder2 Rate:", driveEncoder2->Get());
}
void IAMRobot::TestPeriodic(){

}
