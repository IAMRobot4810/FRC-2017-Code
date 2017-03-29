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
		DigitalInput* pegDetectSensor2, ClimbSystem* climbSystem, ShootSystem* shootSystem):

		a1Toggle(true),
		a2Toggle(true),
		b2Toggle(true),
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
	pDetect2 = pegDetectSensor2;
	dBand = new Deadband();
	scale = new Scaler();
	clb = climbSystem;
	sht = shootSystem;
}

Teleop::~Teleop(){
	delete dBand;
	delete scale;
}

void Teleop::TeleopRun(teleopMode teleMode){
	if(teleMode == OneContNoSensors){
		drv->ArcadeControllerDrive(scale->LinearScale(dBand->DeadbandOut(cont1->GetY(XboxController::kLeftHand), stickDeadband), stickOutSlope, stickOutIntercept, true),
				scale->LinearScale(dBand->DeadbandOut(cont1->GetX(XboxController::kRightHand), stickDeadband), turnStickOutSlope, turnStickOutIntercept, true));
		SmartDashboard::PutNumber("Scaled Stick Output", scale->LinearScale(dBand->DeadbandOut(cont1->GetY(XboxController::kLeftHand), stickDeadband), stickOutSlope, stickOutIntercept, true));

		SmartDashboard::PutNumber("POV", cont1->GetPOV());
		if(cont1->GetPOV() == 0){
			drv->ArcadeControllerDrive(-1.0, 0.0);
		}
		else if(cont1->GetPOV() == 180){
			drv->ArcadeControllerDrive(1.0, 0.0);
		}

		if(cont2->GetBButton() && b2Toggle){
			b2Toggle = false;
			if(gr->raised == true){
				gr->lowerClaw();
			}
			else {
				gr->raiseClaw();
			}
			SmartDashboard::PutBoolean("clawRaised?", gr->raised);
		}
		else if(cont1->GetBButton() == false){
			b2Toggle = true;
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

	else if(teleMode == TwoContNoSensors){

	}

	else if(teleMode == OneContSensors){
		drv->ArcadeControllerDrive(scale->LinearScale(dBand->DeadbandOut(cont1->GetY(XboxController::kLeftHand), stickDeadband), stickOutSlope, stickOutIntercept, true),
				scale->LinearScale(dBand->DeadbandOut(cont1->GetX(XboxController::kRightHand), stickDeadband), turnStickOutSlope, turnStickOutIntercept, true));
		SmartDashboard::PutNumber("Scaled Stick Output", scale->LinearScale(dBand->DeadbandOut(cont1->GetY(XboxController::kLeftHand), stickDeadband), stickOutSlope, stickOutIntercept, true));

		SmartDashboard::PutNumber("POV", cont1->GetPOV());
		if(cont1->GetPOV() == 0){
			drv->ArcadeControllerDrive(-1.0, 0.0);
		}
		else if(cont1->GetPOV() == 180){
			drv->ArcadeControllerDrive(1.0, 0.0);
		}

		if(cont2->GetBButton() && b2Toggle){
			b2Toggle = false;
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
			b2Toggle = true;
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

	else{
		drv->ArcadeControllerDrive(scale->LinearScale(dBand->DeadbandOut(cont1->GetY(XboxController::kLeftHand), stickDeadband), stickOutSlope, stickOutIntercept, true),
				scale->LinearScale(dBand->DeadbandOut(cont1->GetX(XboxController::kRightHand), stickDeadband), turnStickOutSlope, turnStickOutIntercept, true));
		SmartDashboard::PutNumber("Scaled Stick Output", scale->LinearScale(dBand->DeadbandOut(cont1->GetY(XboxController::kLeftHand), stickDeadband), stickOutSlope, stickOutIntercept, true));

		SmartDashboard::PutNumber("POV", cont1->GetPOV());
		if(cont1->GetPOV() == 0){
			drv->ArcadeControllerDrive(-1.0, 0.0);
		}
		else if(cont1->GetPOV() == 180){
			drv->ArcadeControllerDrive(1.0, 0.0);
		}

		if(cont2->GetBumper(GenericHID::kRightHand) && r2BumpToggle){
			r2BumpToggle = false;
			if(gr->raised == true){
				gr->lowerClaw();
			}
			else {
				gr->raiseClaw();
				manualClaw = false;
			}
			SmartDashboard::PutBoolean("clawRaised?", gr->raised);
		}
		else if(cont2->GetBumper(GenericHID::kRightHand) == false){
			r2BumpToggle = true;
		}

		if(cont2->GetBumper(GenericHID::kLeftHand) && l2BumpToggle){
			l2BumpToggle = false;
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
		else if(cont2->GetBumper(GenericHID::kLeftHand) == false){
			l2BumpToggle = true;
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

		if(cont2->GetBButton() && b2Toggle){
			b2Toggle = false;
			manualClaw = true;
			if(gr->raised == true){
				gr->lowerClaw();
			}
			else {
				gr->raiseClaw();
			}
			SmartDashboard::PutBoolean("clawRaised?", gr->raised);
		}
		else if(cont2->GetBButton() == false){
			b2Toggle = true;
		}

		clb->Climb(cont2->GetTriggerAxis(GenericHID::kRightHand));
		if(cont2->GetAButton() && a2Toggle == true){
			a2Toggle = false;
			sht->SpinSequence(10000, 1.0, 0.5, 2.0);
			Wait(5);
			sht->SpinFeed(0.0);
			sht->SpinMeter(0.0);
			sht->SpinShoot(0.0);
		}
		else if(!cont2->GetAButton()){
			a2Toggle = true;
		}
		/*if(cont2->GetAButton()){
			sht->SpinShoot(6000);
		}
		else if(!cont2->GetAButton()){
			sht->SpinShoot(0.0);
		}*/
	}
}
