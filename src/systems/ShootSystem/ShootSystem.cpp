/*
 * ShootSystem.cpp
 *
 *  Created on: Feb 17, 2017
 *      Author: 4810
 */

#include <systems/ShootSystem/ShootSystem.h>

ShootSystem::ShootSystem(CANTalon* feederTalon, CANTalon* meterTalon, CANTalon* shootTalon)
{
	bfeed = feederTalon;
	bfeed->SetInverted(true);
	bmeter = meterTalon;
	bmeter->SetInverted(true);
	bshoot = shootTalon;
	//bshoot->SelectProfileSlot(0);
}

ShootSystem::~ShootSystem(){

}

void ShootSystem::SpinShoot(double speed){
	bshoot->Set(speed);
}

void ShootSystem::SpinMeter(double speed){
	bmeter->Set(speed);
}

void ShootSystem::SpinFeed(double speed){
	bfeed->Set(speed);
}

void ShootSystem::SpinSequence(double shootSpeed, double meterSpeed, double feedSpeed, double spinTime){
	SpinShoot(shootSpeed);
	Wait(spinTime);
	SpinMeter(meterSpeed);
	SpinFeed(feedSpeed);
}
