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
	banner->UpdateTable();
	SmartDashboard::PutBoolean("Banner", banner->Get());
	if(isliftSolenoid && controller->GetBumper(Joystick::kRightHand)){
		isliftSolenoid  = false;
		liftSolenoid->Set(DoubleSolenoid::Value::kReverse);
		Wait(GearPickWaitTime);

	}
	else if(!isliftSolenoid && controller->GetBumper(Joystick::kRightHand)){
		isliftSolenoid  = true;
		liftSolenoid->Set(DoubleSolenoid::Value::kForward);
		Wait(GearPickWaitTime);
	}
	else if(isclampSolenoid && controller->GetBumper(Joystick::kLeftHand)){
		isclampSolenoid = false;
		clampSolenoid->Set(DoubleSolenoid::Value::kReverse);
		Wait(GearPickWaitTime);
	}
	else if(!isclampSolenoid && controller->GetBumper(Joystick::kLeftHand)){
		isclampSolenoid = true;
		clampSolenoid->Set(DoubleSolenoid::Value::kForward);
		Wait(GearPickWaitTime);
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


