/*
 * Teleop.cpp
 *
 *  Created on: Feb 11, 2017
 *      Author: 4810
 */
#include <teleop/Teleop.h>

Teleop::Teleop(XboxController* controller1, XboxController* controller2, DriveSystem* driveSystem,
		GearSystem* gearSystem, DigitalInput* gearDetectSensor, DigitalInput* pegDetectSensor,
		ClimbSystem* climbSystem, BallSystem* ballSystem):

		a1Toggle(true),
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
	pDetect = pegDetectSensor;
	dBand = new Deadband();
	scale = new Scaler();
	clb = climbSystem;
	bll = ballSystem;
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
		if(cont1->GetBumper(GenericHID::kRightHand)){
			clb->IntakeRope(0.3);
		}
		else if(!cont1->GetBumper(GenericHID::kRightHand)){
			clb->IntakeRope(0.0);
		}

		if(cont1->GetBumper(GenericHID::kLeftHand) && l1BumpToggle){
			l1BumpToggle = false;
			if(bll->wallRaised == true){
				bll->LowerWall();
			}
			else {
				bll->RaiseWall();
			}
		}
		else if(cont1->GetBumper(GenericHID::kLeftHand) == false){
			l1BumpToggle = true;
		}

		if(bll->wallRaised == false){
			bll->SpinPickup(cont1->GetTriggerAxis(GenericHID::kLeftHand)/1.5);
		}
		else{
			bll->SpinPickup(cont1->GetTriggerAxis(GenericHID::kLeftHand));
		}
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

		SmartDashboard::PutNumber("Enc1SpeedVal", drv->flE->GetSpeed());
		SmartDashboard::PutNumber("Enc1PosVal", drv->flE->GetRaw());
		SmartDashboard::PutNumber("Enc2SpeedVal", drv->frE->GetSpeed());
		SmartDashboard::PutNumber("Enc2PosVal", drv->frE->GetRaw());

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
		/*if(gDetect->Get()){
			cont1->SetRumble(GenericHID::kRightRumble, 0.0);
		}
		else{
			cont1->SetRumble(GenericHID::kRightRumble, 1.0);
		}*/

		/*SmartDashboard::PutBoolean("Peg?", pDetect->Get());
		if(manualClaw == false && pDetect->Get() == true && gr->raised == true){
			cont1->SetRumble(GenericHID::kRightRumble, 0.0);
			gr->openClaw();
		}
		else if(manualClaw == true && pDetect->Get() == true && gr->raised == true){
			cont1->SetRumble(GenericHID::kLeftRumble, 0.75);
		}
		else{
			cont1->SetRumble(GenericHID::kLeftRumble, 0.0);
		}*/

		if(cont2->GetYButton() && y2Toggle){
			y2Toggle = false;
			clb->Home(0);
		}
		else if(cont2->GetYButton() == false){
			y2Toggle = true;
		}

		clb->Climb(cont1->GetTriggerAxis(GenericHID::kRightHand));
		if(cont1->GetBumper(GenericHID::kRightHand)){
			clb->IntakeRope(0.3);
		}
		else if(!cont1->GetBumper(GenericHID::kRightHand)){
			clb->IntakeRope(0.0);
		}
		SmartDashboard::PutNumber("ClimbPos", clb->clmbTl->GetEncPosition());

		if(cont1->GetBumper(GenericHID::kLeftHand) && l1BumpToggle){
			l1BumpToggle = false;
			if(bll->wallRaised == true){
				bll->LowerWall();
			}
			else {
				bll->RaiseWall();
			}
		}
		else if(cont1->GetBumper(GenericHID::kLeftHand) == false){
			l1BumpToggle = true;
		}

		if(bll->wallRaised == false){
			bll->SpinPickup(cont1->GetTriggerAxis(GenericHID::kLeftHand)/1.5);
		}
		else{
			bll->SpinPickup(cont1->GetTriggerAxis(GenericHID::kLeftHand));
		}

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

		SmartDashboard::PutNumber("Enc1SpeedVal", drv->flE->GetSpeed());
		SmartDashboard::PutNumber("Enc1PosVal", drv->flE->GetRaw());
		SmartDashboard::PutNumber("Enc2SpeedVal", drv->frE->GetSpeed());
		SmartDashboard::PutNumber("Enc2PosVal", drv->frE->GetRaw());

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
				if(gr->raised == false){
					manualClaw = true;
				}
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
		/*if(gDetect->Get()){
			cont1->SetRumble(GenericHID::kRightRumble, 0.0);
		}
		else{
			cont1->SetRumble(GenericHID::kRightRumble, 1.0);
		}*/

		/*SmartDashboard::PutBoolean("Peg?", pDetect->Get());
		if(manualClaw == false && pDetect->Get() == true && gr->raised == true){
			cont1->SetRumble(GenericHID::kRightRumble, 0.0);
			gr->openClaw();
		}
		else if(manualClaw == true && pDetect->Get() == true && gr->raised == true){
			cont1->SetRumble(GenericHID::kLeftRumble, 0.75);
		}
		else{
			cont1->SetRumble(GenericHID::kLeftRumble, 0.0);
		}*/

		if(cont2->GetYButton() && y2Toggle){
			y2Toggle = false;
			clb->Home(0);
		}
		else if(cont2->GetYButton() == false){
			y2Toggle = true;
		}

		clb->Climb(cont2->GetTriggerAxis(GenericHID::kRightHand));
		if(cont2->GetBumper(GenericHID::kRightHand)){
			clb->IntakeRope(0.3);
		}
		else if(!cont2->GetBumper(GenericHID::kRightHand)){
			clb->IntakeRope(0.0);
		}
		SmartDashboard::PutNumber("ClimbPos", clb->clmbTl->GetEncPosition());

		if(cont2->GetBumper(GenericHID::kLeftHand) && l2BumpToggle){
			l2BumpToggle = false;
			if(bll->wallRaised == true){
				bll->LowerWall();
			}
			else {
				bll->RaiseWall();
			}
		}
		else if(cont2->GetBumper(GenericHID::kLeftHand) == false){
			l2BumpToggle = true;
		}

		if(bll->wallRaised == false){
			bll->SpinPickup(cont2->GetTriggerAxis(GenericHID::kLeftHand)/1.5);
		}
		else{
			bll->SpinPickup(cont2->GetTriggerAxis(GenericHID::kLeftHand));
		}
	}
}
