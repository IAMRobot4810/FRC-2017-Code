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

void GearPickup::teleopGearLoopSensor(){
	if(controller->GetBButton() && liftSolenoidToggle){
			liftSolenoidToggle = false;
			if(liftSolenoid->Get() == DoubleSolenoid::Value::kForward){
				liftSolenoid->Set(DoubleSolenoid::Value::kReverse);
			}
			else {
				liftSolenoid->Set(DoubleSolenoid::Value::kForward);
				clawControl = false;
			}
		}
		else if(controller->GetBButton() == false){
			liftSolenoidToggle = true;
		}

		if(controller->GetAButton() && clampSolenoidToggle){
			clampSolenoidToggle = false;
			clawControl = true;
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
		if(clawControl == false && banner->Get() == false && liftSolenoid->Get() == DoubleSolenoid::Value::kReverse){
					controller->SetRumble(GenericHID::kRightRumble, 0.0);
					clampSolenoid->Set(DoubleSolenoid::Value::kReverse);
					liftSolenoid->Set(DoubleSolenoid::Value::kForward);
				}
				else if(clawControl == true && liftSolenoid->Get() == DoubleSolenoid::Value::kReverse && liftSolenoid->Get() == DoubleSolenoid::Value::kReverse){
					controller->SetRumble(GenericHID::kRightRumble, 1.0);
				}
				else{
					controller->SetRumble(GenericHID::kRightRumble, 0.0);
				}
}
void GearPickup::teleopGearLoopMod(){
	if(controller->GetBumper(GenericHID::kRightHand) && liftSolenoidToggle){
		liftSolenoidToggle = false;
		if(liftSolenoid->Get() == DoubleSolenoid::Value::kForward){
			liftSolenoid->Set(DoubleSolenoid::Value::kReverse);
		}
		else {
			liftSolenoid->Set(DoubleSolenoid::Value::kForward);
		}
	}
	else if(controller->GetBumper(GenericHID::kRightHand) == false){
		liftSolenoidToggle = true;
	}

	if(controller->GetBumper(GenericHID::kLeftHand) && clampSolenoidToggle){
		clampSolenoidToggle = false;
		if(clampSolenoid->Get() == DoubleSolenoid::Value::kForward){
			clampSolenoid->Set(DoubleSolenoid::Value::kReverse);
		}
		else {
			clampSolenoid->Set(DoubleSolenoid::Value::kForward);
		}
	}
	else if(controller->GetBumper(GenericHID::kLeftHand) == false){
		clampSolenoidToggle = true;
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

bool GearPickup::getIsGear(){
	if(banner->Get()){
		return false;
	}

	else {
		return true;
	}
}




