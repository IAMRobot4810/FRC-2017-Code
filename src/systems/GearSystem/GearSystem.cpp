/*
 * GearSystem.cpp
 *
 *  Created on: Feb 12, 2017
 *      Author: 4810
 */

#include <systems/GearSystem/GearSystem.h>

GearSystem::GearSystem(DoubleSolenoid* liftSolenoid, DoubleSolenoid* clawSolenoid):
	raised(true),
	open(false)
{
	liftNoid = liftSolenoid;
	clawNoid = clawSolenoid;
}

GearSystem::~GearSystem(){

}

void GearSystem::raiseClaw(){
	raised = true;
	liftNoid->Set(DoubleSolenoid::kForward);
}

void GearSystem::lowerClaw(){
	raised = false;
	liftNoid->Set(DoubleSolenoid::kReverse);
}

void GearSystem::openClaw(){
	open = true;
	clawNoid->Set(DoubleSolenoid::kForward);
}

void GearSystem::closeClaw(){
	open = false;
	clawNoid->Set(DoubleSolenoid::kReverse);
}
