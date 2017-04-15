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

	//bshoot properties
	bshoot->SetFeedbackDevice(CANTalon::CtreMagEncoder_Relative); //Using a CTRE Mag Encoder
	bshoot->SetSensorDirection(false); //Reversing the sensor count direction
	bshoot->SetInverted(true); //Reversing the Talon
	bshoot->ConfigNominalOutputVoltage(0.0, 0.0); //Configuring lowest voltage to motor *NEEDS TESTING*
	bshoot->ConfigPeakOutputVoltage(12.0, -12.0); //Configuring peak voltage to motor *NEEDS TESTING*
	bshoot->SetEncPosition(0); //Zeroing PID accumulation and sensor
	bshoot->SetPosition(0.0); //'
	bshoot->ClearIaccum(); //'

}

ShootSystem::~ShootSystem(){

}

void ShootSystem::SpinShoot(double shootPow){
	bshoot->Set(shootPow);
}

void ShootSystem::SpinShootEncoder(double speed){
	if(speed == 0){
		bshoot->Set(0.0);
	}
	else{
		bshoot->Set(pow(((speed-(bshoot->GetSpeed()))/(shootDivisor*speed)), shootPowFactor));
	}
}

void ShootSystem::SpinMeter(double speed){
	bmeter->Set(speed);
}

/*void ShootSystem::UnjamFeed(double speed){
	if(powerPanel->GetCurrent(2) > 9.0){
		Wait(0.75);
		if(powerPanel->GetCurrent(2) > 9.0){
			bfeed->Set(-speed);
			Wait(0.25);
		}
	}
}*/

void ShootSystem::SpinFeed(double speed){
	bfeed->Set(speed);
	//UnjamFeed(speed);
}

/*void ShootSystem::SpinSequence(double shootSpeed, double meterSpeed, double feedSpeed, double spinTime, double shootTime){
	SpinShoot(shootSpeed);
	Wait(spinTime);
	SpinMeter(meterSpeed);
	SpinFeed(feedSpeed);
	Wait(shootTime);
	SpinMeter(0.0);
	SpinFeed(0.0);
	SpinShoot(0.0);
}

void ShootSystem::SpinSequenceMod(double shootSpeed, double meterSpeed, double feedSpeed, double spinTime, double shootTime){
	//if(bshoot->GetSpeed()<)
}

void ShootSystem::SpinSequenceCalibrated(double shootSpeed, double meterSpeed, double feedSpeed, double spinTime, double shootTime, double threshold, double power){
	bshoot->SetTalonControlMode(CANTalon::kThrottleMode);
	if(bshoot->GetSpeed() <= threshold){
		bshoot->Set(pow((shootSpeed-(bshoot->GetSpeed()))/shootSpeed,power));
	} else if(bshoot->GetSpeed() > threshold && bshoot->GetSpeed() <= shootSpeed ){
		bshoot->Set(pow((shootSpeed-(bshoot->GetSpeed()))/shootSpeed,power));
		bfeed->Set(feedSpeed);
		bmeter->Set(meterSpeed);
	}else{
		bshoot->Set(0);
	}
}

void ShootSystem::SpinSequenceVoltage(double shootSpeed, double meterSpeed, double feedSpeed, double spinTime, double shootTime, double threshold, double power){
	bshoot->SetTalonControlMode(CANTalon::kVoltageMode);
	if(bshoot->GetSpeed() <= threshold){
		bshoot->Set(10*(pow((shootSpeed-(bshoot->GetSpeed()))/shootSpeed,power)));
	} else if(bshoot->GetSpeed() > threshold && bshoot->GetSpeed() <= shootSpeed ){
		bshoot->Set(10*(pow((shootSpeed-(bshoot->GetSpeed()))/shootSpeed,power)));
		bfeed->Set(feedSpeed);
		bmeter->Set(meterSpeed);
	}else{
		bshoot->Set(0);
	}
}*/

