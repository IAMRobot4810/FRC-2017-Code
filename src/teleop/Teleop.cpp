/*
 * Teleop.cpp
 *
 *  Created on: Feb 11, 2017
 *      Author: 4810
 */
#include <teleop/Teleop.h>
#include <iostream>

Teleop::Teleop(XboxController* controller1, XboxController* controller2, DriveSystem* driveSystem,
		GearSystem* gearSystem, DigitalInput* gearDetectSensor, DigitalInput* pegDetectSensor1,
		ClimbSystem* climbSystem, ShootSystem* shootSystem):

		a1Toggle(true),
		a2Toggle(true),
		b1Toggle(true),
		y2Toggle(true),
		l1BumpToggle(true),
		r1BumpToggle(true),
		l2BumpToggle(true),
		r2BumpToggle(true),
		manualClaw(false)

{
	drv = driveSystem;
	gr = gearSystem;
	cont1 = controller1;
	cont2 = controller2;
	gDetect = gearDetectSensor;
	pDetect1 = pegDetectSensor1;
	dBand = new Deadband();
	scale = new Scaler();
	clb = climbSystem;
	sht = shootSystem;
}

Teleop::~Teleop(){
	delete dBand;
	delete scale;
}

void Teleop::TeleopTwoController(bool sensors){
	if(!sensors){

	}

	else{
		drv->ArcadeControllerDrive(scale->LinearScale(dBand->DeadbandOut(cont1->GetY(XboxController::kLeftHand), stickDeadband), stickOutSlope, stickOutIntercept, true),
				scale->LinearScale(dBand->DeadbandOut(cont1->GetX(XboxController::kRightHand), stickDeadband), turnStickOutSlope, turnStickOutIntercept, true));

		if(cont1->GetPOV() == 0){
			drv->ArcadeControllerDrive(-1.0, 0.0);
		}
		else if(cont1->GetPOV() == 180){
			drv->ArcadeControllerDrive(1.0, 0.0);
		}

		if(cont1->GetBumper(GenericHID::kRightHand) && r1BumpToggle){
			r1BumpToggle = false;
			if(gr->raised == true){
				gr->lowerClaw();
			}
			else {
				gr->raiseClaw();
				manualClaw = false;
			}
			SmartDashboard::PutBoolean("clawRaised?", gr->raised);
		}
		else if(cont1->GetBumper(GenericHID::kRightHand) == false){
			r1BumpToggle = true;
		}

		if(cont1->GetBumper(GenericHID::kLeftHand) && l1BumpToggle){
			l1BumpToggle = false;
			if(gr->open == true){
				gr->closeClaw();
				manualClaw = true;
			}
			else {
				gr->openClaw();
			}
			SmartDashboard::PutBoolean("clawOpen?", gr->open);
		}
		else if(cont1->GetBumper(GenericHID::kLeftHand) == false){
			l1BumpToggle = true;
		}

		SmartDashboard::PutBoolean("Gear?", !gDetect->Get());
		if(manualClaw == false && gDetect->Get() == false && gr->raised == false){
			cont1->SetRumble(GenericHID::kRightRumble, 0.0);
			gr->closeClaw();
			Wait(0.5);
			gr->raiseClaw();
		}
		else if(manualClaw == true && gDetect->Get() == false && gr->raised == false){
			cont1->SetRumble(GenericHID::kRightRumble, 1.0);
		}
		else{
			cont1->SetRumble(GenericHID::kRightRumble, 0.0);
		}

		if(cont1->GetBButton() && b1Toggle){
			b1Toggle = false;
			manualClaw = true;
			if(gr->raised == true){
				gr->lowerClaw();
			}
			else {
				gr->raiseClaw();
			}
			SmartDashboard::PutBoolean("clawRaised?", gr->raised);
		}
		else if(cont1->GetBButton() == false){
			b1Toggle = true;
		}

		if(cont2->GetTriggerAxis(GenericHID::kRightHand) > 0.1 && cont2->GetTriggerAxis(GenericHID::kLeftHand) <= 0.1){
			clb->Climb(cont2->GetTriggerAxis(GenericHID::kRightHand));
		}
		else if(cont2->GetTriggerAxis(GenericHID::kLeftHand) > 0.1 && cont2->GetTriggerAxis(GenericHID::kRightHand) <= 0.1){
			clb->Climb(-cont2->GetTriggerAxis(GenericHID::kLeftHand));
		}
		else{
			clb->Climb(STOP);
		}

		if(cont2->GetBumper(GenericHID::kLeftHand)){
			sht->SpinShootEncoder(midAutoShootRPM);
		}
		else if(!cont2->GetBumper(GenericHID::kLeftHand)){
			sht->SpinShootEncoder(STOP);
		}
		//sht->SpinShoot(cont2->GetTriggerAxis(GenericHID::kLeftHand));
		if(cont2->GetBumper(GenericHID::kRightHand) && !cont2->GetBButton()){
			sht->SpinMeter(meterPow);
			sht->SpinFeed(feedPow);
		}
		else if(!cont2->GetBumper(GenericHID::kRightHand) && cont2->GetBButton()){
			sht->SpinMeter(STOP);
			sht->SpinFeed(-feedPow);
		}
		else if(cont2->GetBumper(GenericHID::kRightHand) && cont2->GetBButton()){
			sht->SpinMeter(STOP);
			sht->SpinFeed(-feedPow);
		}
		else{
			sht->SpinMeter(STOP);
			sht->SpinFeed(STOP);
		}

	}
}

void Teleop::TeleopOneController(bool sensors){
	if(!sensors){
		drv->ArcadeControllerDrive(scale->LinearScale(dBand->DeadbandOut(cont1->GetY(XboxController::kLeftHand), stickDeadband), stickOutSlope, stickOutIntercept, true),
				scale->LinearScale(dBand->DeadbandOut(cont1->GetX(XboxController::kRightHand), stickDeadband), turnStickOutSlope, turnStickOutIntercept, true));

		if(cont1->GetPOV() == 0){
			drv->ArcadeControllerDrive(-1.0, 0.0);
		}
		else if(cont1->GetPOV() == 180){
			drv->ArcadeControllerDrive(1.0, 0.0);
		}

		if(cont1->GetBButton() && b1Toggle){
			b1Toggle = false;
			if(gr->raised == true){
				gr->lowerClaw();
			}
			else {
				gr->raiseClaw();
			}
			SmartDashboard::PutBoolean("clawRaised?", gr->raised);
		}
		else if(cont1->GetBButton() == false){
			b1Toggle = true;
		}

		if(cont1->GetAButton() && a1Toggle){
			a1Toggle = false;
			if(gr->open == true){
				gr->closeClaw();
			}
			else {
				gr->openClaw();
			}
			SmartDashboard::PutBoolean("clawOpen?", gr->open);
		}
		else if(cont1->GetAButton() == false){
			a1Toggle = true;
		}

		clb->Climb(cont1->GetTriggerAxis(GenericHID::kRightHand));
	}

	else{
		drv->ArcadeControllerDrive(scale->LinearScale(dBand->DeadbandOut(cont1->GetY(XboxController::kLeftHand), stickDeadband), stickOutSlope, stickOutIntercept, true),
				scale->LinearScale(dBand->DeadbandOut(cont1->GetX(XboxController::kRightHand), stickDeadband), turnStickOutSlope, turnStickOutIntercept, true));

		if(cont1->GetPOV() == 0){
			drv->ArcadeControllerDrive(-1.0, 0.0);
		}
		else if(cont1->GetPOV() == 180){
			drv->ArcadeControllerDrive(1.0, 0.0);
		}

		if(cont1->GetBButton() && b1Toggle){
			b1Toggle = false;
			if(gr->raised == true){
				gr->lowerClaw();
			}
			else {
				gr->raiseClaw();
				manualClaw = false;
			}
			SmartDashboard::PutBoolean("clawRaised?", gr->raised);
		}
		else if(cont1->GetBButton() == false){
			b1Toggle = true;
		}

		if(cont1->GetAButton() && a1Toggle){
			a1Toggle = false;
			if(gr->open == true){
				gr->closeClaw();
				manualClaw = true;
			}
			else {
				gr->openClaw();
				if(gr->raised == false){
					manualClaw = true;
				}
			}
			SmartDashboard::PutBoolean("clawOpen?", gr->open);
		}
		else if(cont1->GetAButton() == false){
			a1Toggle = true;
		}

		SmartDashboard::PutBoolean("Gear?", !gDetect->Get());
		if(manualClaw == false && gDetect->Get() == false && gr->raised == false){
			cont1->SetRumble(GenericHID::kRightRumble, 0.0);
			gr->closeClaw();
			Wait(0.5);
			gr->raiseClaw();
		}
		else if(manualClaw == true && gDetect->Get() == false && gr->raised == false){
			cont1->SetRumble(GenericHID::kRightRumble, 1.0);
		}
		else{
			cont1->SetRumble(GenericHID::kRightRumble, 0.0);
		}

		clb->Climb(cont1->GetTriggerAxis(GenericHID::kRightHand));

	}
}
