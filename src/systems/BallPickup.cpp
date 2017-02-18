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
	Ball_BackDoor = new Solenoid(backDoorID);
}

Ball_Pickup::~Ball_Pickup() {
	delete control;
	delete innerRoller;
	delete outerRoller;
	delete Ball_BackDoor;

}

void Ball_Pickup::TeleopBallLoop(){

}

void Ball_Pickup::BallInput(){
	innerRoller->Set(1);
	outerRoller->Set(-1);
	Ball_BackDoor->Set(true);
}

void Ball_Pickup::BallOutput(){
	innerRoller->Set(-1);
	outerRoller->Set(1);
	Ball_BackDoor->Set(false);
}



