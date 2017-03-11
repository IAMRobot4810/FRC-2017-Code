/*
 * BallSystem.cpp
 *
 *  Created on: Feb 17, 2017
 *      Author: 4810
 */

#include <systems/BallSystem/BallSystem.h>

BallSystem::BallSystem(CANTalon* outerWallTalon, CANTalon* innerWallTalon, DoubleSolenoid* wallSolenoid):
	wallRaised(false)
{
	b1Tl = outerWallTalon;
	b2Tl = innerWallTalon;
	blSl = wallSolenoid;
}

BallSystem::~BallSystem(){

}

void BallSystem::SpinPickup(double speed){
	b1Tl->Set(-speed);
	b2Tl->Set(-speed);
}

void BallSystem::RaiseWall(){
	blSl->Set(DoubleSolenoid::kReverse);
	wallRaised = true;
}

void BallSystem::LowerWall(){
	b2Tl->Set(0.25);
	blSl->Set(DoubleSolenoid::kForward);
	wallRaised = false;
	b2Tl->StopMotor();
}
