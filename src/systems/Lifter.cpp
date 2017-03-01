/*
 * Lifter.cpp
 *
 *  Created on: Feb 17, 2017
 *      Author: Anish
 */

#include <systems/Lifter.h>

Lifter::Lifter(XboxController* controller) {
	this->controller = controller;
	leftInRoller = new CANTalon(leftInRollerID);
	rightInRoller = new CANTalon(rightInRollerID);
	liftTalon = new CANTalon(lifterTalonID);
}

Lifter::~Lifter() {
	delete controller;
	delete leftInRoller;
	delete rightInRoller;
	delete liftTalon;
}

void Lifter::TeleopLoop(){
	if(controller->GetBumper(GenericHID::kRightHand)){
		leftInRoller->Set(RollerSpeed);
		rightInRoller->Set(-1*RollerSpeed);
	}
	else if(!controller->GetBumper(GenericHID::kRightHand)){
		leftInRoller->Set(0);
		rightInRoller->Set(0);
	}
	if(controller->GetTriggerAxis(GenericHID::kRightHand)){
		liftTalon->Set(-1*controller->GetTriggerAxis(GenericHID::kRightHand));
	}
	else{
		liftTalon->Set(0);
	}
}




