/*
 * DriveSystem.cpp
 *
 *  Created on: Feb 10, 2017
 *      Author: Anish
 */


#include "DriveSystem.h"
using namespace frc;


DriveSystem::DriveSystem(XboxController* mainController) {
	flTalon = new CANTalon(flTalID);
	frTalon = new CANTalon(frTalID);
	rlTalon = new CANTalon(rlTalID);
	rrTalon = new CANTalon(rrTalID);
	drive  = new RobotDrive(flTalon,rlTalon,frTalon,rrTalon);
	driveEncoder1 = new Encoder(flEncID1,flEncID2,true,Encoder::EncodingType::k4X);
	driveEncoder2 = new Encoder(frEncID1,frEncID2,true,Encoder::EncodingType::k4X);
	controller = mainController;
	driveband = new Deadband(LowLimitDriveDeadband,HighLimitDriveDeadband);
}

DriveSystem::~DriveSystem() {
	delete drive;
	delete driveEncoder1;
	delete driveEncoder2;
	delete flTalon;
	delete frTalon;
	delete rlTalon;
	delete rrTalon;
	delete controller;
	delete driveband;
}



void DriveSystem::ArcadeDriveStick(){
	drive->ArcadeDrive(driveband->ReturnBoundedValue(controller->GetY(Joystick::kLeftHand)), driveband->ReturnBoundedValue(controller->GetX(Joystick::kRightHand)), false);
}

void DriveSystem::TankDriveStick(){
	drive->TankDrive(driveband->ReturnBoundedValue(controller->GetY(Joystick::kLeftHand)),driveband->ReturnBoundedValue(controller->GetY(Joystick::kRightHand)),false);
}

void DriveSystem::ArcadeDriveStickSquare(){
	drive->ArcadeDrive(driveband->ReturnBoundedValue(controller->GetY(Joystick::kLeftHand)), driveband->ReturnBoundedValue(controller->GetX(Joystick::kRightHand)), true);
}
void DriveSystem::TankDriveStickSquare(){
	drive->TankDrive(driveband->ReturnBoundedValue(controller->GetY(Joystick::kLeftHand)),driveband->ReturnBoundedValue(controller->GetY(Joystick::kRightHand)),true);
}

