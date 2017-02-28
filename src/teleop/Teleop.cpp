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
		y1Toggle(true),
		lBumpToggle(true),
		rBumpToggle(true),
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

void Teleop::TeleopRun(bool sensors){
	if(sensors == true){
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
		SmartDashboard::PutNumber("Enc2PosVal", drv->frE->GetRaw());
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
			manualClaw = true;
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

		SmartDashboard::PutBoolean("Gear?", !gDetect->Get());
		if(manualClaw == false && gDetect->Get() == false && gr->raised == false){
			cont1->SetRumble(GenericHID::kRightRumble, 0.0);
			gr->closeClaw();
			gr->raiseClaw();
		}
		else if(manualClaw == true && gDetect->Get() == false && gr->raised == false){
			cont1->SetRumble(GenericHID::kRightRumble, 1.0);
		}
		else{
			cont1->SetRumble(GenericHID::kRightRumble, 0.0);
		}

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

		if(cont1->GetYButton() && y1Toggle){
			y1Toggle = false;
			clb->Home(0);
		}
		else if(cont1->GetYButton() == false){
			y1Toggle = true;
		}

		clb->Climb(cont1->GetTriggerAxis(GenericHID::kRightHand));
		if(cont1->GetBumper(GenericHID::kRightHand)){
			clb->IntakeRope(0.3);
		}
		else if(!cont1->GetBumper(GenericHID::kRightHand)){
			clb->IntakeRope(0.0);
		}
		SmartDashboard::PutNumber("ClimbPos", clb->clmbTl->GetEncPosition());

		if(cont1->GetBumper(GenericHID::kLeftHand) && lBumpToggle){
			lBumpToggle = false;
			if(bll->wallRaised == true){
				bll->LowerWall();
			}
			else {
				bll->RaiseWall();
			}
		}
		else if(cont1->GetBumper(GenericHID::kLeftHand) == false){
			lBumpToggle = true;
		}

		bll->SpinPickup(cont1->GetTriggerAxis(GenericHID::kLeftHand));

	}

	else{

	}
}
