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
	Ball_BackDoor = new DoubleSolenoid(PCM_ID,backDoorID1,backDoorID2);
}

Ball_Pickup::~Ball_Pickup() {
	delete control;
	delete innerRoller;
	delete outerRoller;
	delete Ball_BackDoor;

}

void Ball_Pickup::TeleopBallLoopToggled(){
	if(control->GetBumper(GenericHID::kLeftHand) && elevatorToggle){
		elevatorToggle = false;
		if(Ball_BackDoor->Get() == DoubleSolenoid::Value::kForward){
			LowElevator();
		}
		else {
			RaiseElevator();
		}
	}
	else if(control->GetBumper(GenericHID::kLeftHand) == false){
		elevatorToggle = true;
	}

	if(control->GetTriggerAxis(GenericHID::kLeftHand)){
			BallOutput(control->GetTriggerAxis(GenericHID::kLeftHand));
	}
	else{
		BallOutput(0);
	}
}
void Ball_Pickup::BallInput(double speed){
	innerRoller->Set(speed);
	outerRoller->Set(speed);
}

void Ball_Pickup::BallOutput(double speed){
	innerRoller->Set(speed);
	outerRoller->Set(-1*speed);
}

void Ball_Pickup::RaiseElevator(){
	Ball_BackDoor->Set(DoubleSolenoid::Value::kForward);
}

void Ball_Pickup::LowElevator(){
	Ball_BackDoor->Set(DoubleSolenoid::Value::kReverse);
}


