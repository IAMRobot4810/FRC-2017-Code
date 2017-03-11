/*
 * ClimbSystem.cpp
 *
 *  Created on: Feb 17, 2017
 *      Author: 4810
 */

#include <systems/ClimbSystem/ClimbSystem.h>

ClimbSystem::ClimbSystem(CANTalon* climbTalon, CANTalon* leftIntakeTalon, CANTalon* rightIntakeTalon){
	clmbTl = climbTalon;
	rInTal = rightIntakeTalon;
	lInTal = leftIntakeTalon;

	clmbTl->SetFeedbackDevice(CANTalon::CtreMagEncoder_Absolute);
}

ClimbSystem::~ClimbSystem(){

}

void ClimbSystem::IntakeRope(double speed){
	lInTal->Set(-speed);
	rInTal->Set(speed);
}

void ClimbSystem::Climb(double speed){
	clmbTl->SetControlMode(CANTalon::kPercentVbus);
	clmbTl->EnableControl();
	clmbTl->Set(-speed);

}

void ClimbSystem::Home(double pos){
	clmbTl->SetControlMode(CANTalon::kPosition);
	clmbTl->SetP(0.12);
	clmbTl->EnableControl();
	clmbTl->Set(0.0);
}
