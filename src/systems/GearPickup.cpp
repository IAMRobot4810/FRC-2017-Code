/*
 * GearPickup.cpp
 *
 *  Created on: Feb 11, 2017
 *      Author: Anish
 */

#include <systems/GearPickup.h>

GearPickup::GearPickup(XboxController*controller) {
	this->controller = controller;
	liftSolenoid = new DoubleSolenoid(PCM_ID, liftSolenoidID1,liftSolenoidID2);
	clampSolenoid = new DoubleSolenoid(PCM_ID,clampSolenoidID1,clampSolenoidID2);
	banner = new DigitalInput(BannerID);
}

GearPickup::~GearPickup() {
	delete controller;
	delete liftSolenoid;
	delete clampSolenoid;
	delete banner;
}

void GearPickup::teleopGearLoop(){

	if(controller->GetBButton() && liftSolenoidToggle){
		liftSolenoidToggle = false;
		if(liftSolenoid->Get() == DoubleSolenoid::Value::kForward){
			liftSolenoid->Set(DoubleSolenoid::Value::kReverse);
		}
		else {
			liftSolenoid->Set(DoubleSolenoid::Value::kForward);
		}
	}
	else if(controller->GetBButton() == false){
		liftSolenoidToggle = true;
	}

	if(controller->GetAButton() && clampSolenoidToggle){
		clampSolenoidToggle = false;
		if(clampSolenoid->Get() == DoubleSolenoid::Value::kForward){
			clampSolenoid->Set(DoubleSolenoid::Value::kReverse);
		}
		else {
			clampSolenoid->Set(DoubleSolenoid::Value::kForward);
		}
	}
	else if(controller->GetAButton() == false){
		clampSolenoidToggle = true;
	}

}

void GearPickup::teleopGearLoopMod(){
	if(liftSolenoid->Get() == DoubleSolenoid::Value::kForward && controller->GetBumper(Joystick::kRightHand)){
		liftSolenoid->Set(DoubleSolenoid::Value::kReverse);
		Wait(GearPickWaitTime);
	}
	else if(liftSolenoid->Get() == DoubleSolenoid::Value::kReverse && controller->GetBumper(Joystick::kRightHand)){
		liftSolenoid->Set(DoubleSolenoid::Value::kForward);
		Wait(GearPickWaitTime);
	}
	else if (clampSolenoid->Get() == DoubleSolenoid::Value::kReverse && controller->GetBumper(Joystick::kLeftHand)){
		clampSolenoid->Set(DoubleSolenoid::Value::kForward);
		Wait(GearPickWaitTime);
	}
	else if(clampSolenoid->Get() == DoubleSolenoid::Value::kForward && controller->GetBumper(Joystick::kLeftHand)){
		clampSolenoid->Set(DoubleSolenoid::Value::kReverse);
		Wait(GearPickWaitTime);
	}
}

void GearPickup::teleopGearLoopMod2(){
	if(liftSolenoid->Get() == DoubleSolenoid::Value::kForward && controller->GetBumper(Joystick::kRightHand)){
		while(liftSolenoid->Get() != DoubleSolenoid::Value::kReverse){
			liftSolenoid->Set(DoubleSolenoid::Value::kReverse);
		}
	}
	else if(liftSolenoid->Get() == DoubleSolenoid::Value::kReverse && controller->GetBumper(Joystick::kRightHand)){
		while(liftSolenoid->Get() != DoubleSolenoid::Value::kForward){
			liftSolenoid->Set(DoubleSolenoid::Value::kForward);
		}
	}
	else if (clampSolenoid->Get() == DoubleSolenoid::Value::kReverse && controller->GetBumper(Joystick::kLeftHand)){
		while(clampSolenoid->Get() != DoubleSolenoid::Value::kForward){
			clampSolenoid->Set(DoubleSolenoid::Value::kForward);
		}
	}
	else if(clampSolenoid->Get() == DoubleSolenoid::Value::kForward && controller->GetBumper(Joystick::kLeftHand)){
		while(liftSolenoid->Get() != DoubleSolenoid::Value::kReverse){
			liftSolenoid->Set(DoubleSolenoid::Value::kReverse);
		}
	}
}


