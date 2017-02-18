/*
 * GearPickup.cpp
 *
 *  Created on: Feb 11, 2017
 *      Author: Anish
 */

#include <systems/GearPickup.h>

GearPickup::GearPickup(XboxController*controller) {
	this->controller = controller;
	liftSolenoid = new Solenoid(PCM_ID,liftSolenoidID);
	clampSolenoid = new Solenoid(PCM_ID,clampSolenoidID);
	banner = new DigitalInput(BannerID);
}

GearPickup::~GearPickup() {
	delete controller;
	delete liftSolenoid;
	delete clampSolenoid;
	delete banner;
}

void GearPickup::teleopGearLoop(){
	banner->UpdateTable();
	SmartDashboard::PutBoolean("Banner", banner->Get());
	if(isliftSolenoid && controller->GetBumper(Joystick::kRightHand)){
		isliftSolenoid  = false;
		liftSolenoid->Set(false);
		Wait(GearPickWaitTime);

	}
	else if(!isliftSolenoid && controller->GetBumper(Joystick::kRightHand)){
		isliftSolenoid  = true;
		liftSolenoid->Set(true);
		Wait(GearPickWaitTime);
	}
	else if(isclampSolenoid && controller->GetBumper(Joystick::kLeftHand)){
		isclampSolenoid = false;
		clampSolenoid->Set(false);
		Wait(GearPickWaitTime);
	}
	else if(!isclampSolenoid && controller->GetBumper(Joystick::kLeftHand)){
		isclampSolenoid = true;
		clampSolenoid->Set(true);
		Wait(GearPickWaitTime);
	}

}

void GearPickup::teleopGearLoopMod(){

}


