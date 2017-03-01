/*
 * BallPickup.cpp
 *
 *  Created on: Feb 17, 2017
 *      Author: Anish
 */

#include <systems/BallPickup.h>

Ball_Pickup::Ball_Pickup(XboxController* controller) {
	this->control = controller;
	innerRoller = new CANTalon(innerRollerID);
	outerRoller = new CANTalon(outerRollerID);
	Ball_BackDoor = new DoubleSolenoid(backDoorID1,backDoorID2);
}

Ball_Pickup::~Ball_Pickup() {
	delete control;
	delete innerRoller;
	delete outerRoller;
	delete Ball_BackDoor;

}

void Ball_Pickup::TeleopBallLoop(){
	if(control->GetXButton() && !control->GetYButton()){
		BallInput();
	}
	else if(control->GetYButton() && !control->GetXButton()){
		BallOutput();
	}

	else if(control->GetTriggerAxis(Joystick::kRightHand) && !control->GetTriggerAxis(Joystick::kLeftHand)){
		RaiseElevator();
	}
	else if(control->GetTriggerAxis(Joystick::kRightHand) && !control->GetTriggerAxis(Joystick::kLeftHand)){
		LowElevator();
	}

	else{
		innerRoller->Set(0);
		outerRoller->Set(0);
	}
}

void Ball_Pickup::BallInput(){
	innerRoller->Set(1);
	outerRoller->Set(1);
}

void Ball_Pickup::BallOutput(){
	innerRoller->Set(-1);
	outerRoller->Set(-1);
}

void Ball_Pickup::RaiseElevator(){
	Ball_BackDoor->Set(DoubleSolenoid::Value::kForward);
}

void Ball_Pickup::LowElevator(){
	Ball_BackDoor->Set(DoubleSolenoid::Value::kReverse);
}


