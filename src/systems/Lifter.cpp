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
	if(controller->GetAButton()&& !controller->GetBButton()){
		leftInRoller->Set(RollerSpeed);
		rightInRoller->Set(RollerSpeed);
		liftTalon->Set(LiftSpeed);
	}
	else if(controller->GetBButton() && !controller->GetAButton()){
		leftInRoller->Set(-1*RollerSpeed);
		rightInRoller->Set(-1*RollerSpeed);
		liftTalon->Set(-1*LiftSpeed);
	}
	else{
		leftInRoller->Set(0);
		rightInRoller->Set(0);
		liftTalon->Set(0);
	}
}




