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

}

GearPickup::~GearPickup() {
	delete controller;
	delete liftSolenoid;
	delete clampSolenoid;
}

void GearPickup::teleopGearLoop(){
	/*
	if(controller->GetXButton() && !liftSolenoid->Get()){
		liftSolenoid->Set(true);
	}else if(controller->GetXButton() && liftSolenoid->Get()){
		liftSolenoid->Set(false);
	}
	if(controller->GetYButton() && !clampSolenoid->Get()){
		clampSolenoid->Set(true);
	}else if(controller->GetYButton() && !clampSolenoid->Get()){
		clampSolenoid->Set(false);
	}
	*/
	if(isliftSolenoid && controller->GetXButton()){
		isliftSolenoid  = false;
		liftSolenoid->Set(false);
		Wait(0.5);
	}
	else if(!isliftSolenoid && controller->GetXButton()){
		isliftSolenoid  = true;
		liftSolenoid->Set(true);
		Wait(0.5);
	}
	else if(isclampSolenoid && controller->GetYButton()){
		isclampSolenoid = false;
		clampSolenoid->Set(false);
		Wait(0.5);
	}
	else if(!isclampSolenoid && controller->GetYButton()){
		isclampSolenoid = true;
		clampSolenoid->Set(true);
		Wait(0.5);
	}

}
