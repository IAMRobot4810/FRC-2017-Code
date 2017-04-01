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

void ShootSystem::SpinSequence(double shootSpeed, double meterSpeed, double feedSpeed, double spinTime, double shootTime){
	/*
	for(int i = 0; i < (spinTime*100); i++){
		if(bshoot->GetSpeed()<shootSpeed){
			bshoot->Set(pow(((shootSpeed - bshoot->GetSpeed())/shootSpeed), powFactor));
		}else{
			bshoot->Set(0);
		}
		Wait(0.1);
	}
	for(int i = 0; i < (shootTime*100); i++){
		SpinMeter(meterSpeed);
		SpinFeed(feedSpeed);
		if(bshoot->GetSpeed()<shootSpeed){
			bshoot->Set(pow(((shootSpeed - bshoot->GetSpeed())/shootSpeed), powFactor));
		}else{
			bshoot->Set(0);
		}
		Wait(0.1);
	}
	*/
	/*if(bshoot->GetSpeed()<shootSpeed){
		bshoot->Set(pow(((shootSpeed - bshoot->GetSpeed())/shootSpeed), powFactor));
	}else if(){
		bshoot->Set(0);
	}
	SpinMeter(0.0);
	SpinFeed(0.0);
	SpinShoot(0.0);*/
	SpinShoot(shootSpeed);
	Wait(spinTime);
	SpinMeter(meterSpeed);
	SpinFeed(feedSpeed);
	Wait(shootTime);
	SpinMeter(0.0);
		SpinFeed(0.0);
		SpinShoot(0.0);


}
