/*
 * Auto.cpp
 *
 *  Created on: Feb 21, 2017
 *      Author: 4810
 *
 *  Source file for Auto.h
 */

#include <auto/Auto.h>

Auto::Auto(DriveSystem* driveSystem, GearSystem* gearSystem, DigitalInput* gearDetectSensor,
		DigitalInput* pegDetectSensor1, ShootSystem* shootSystem){ //Constructor
	drv = driveSystem;
	gr = gearSystem;
	gDetect = gearDetectSensor;
	pDetect1 = pegDetectSensor1;
	sht = shootSystem;
	powerPanel = new PowerDistributionPanel(pdpID);

	jamCycles = 0;
	unjamCycles = 0;

	/*//Vision stuff with PixyCam
	duino = new SerialPort(9600, SerialPort::kUSB1);
	buff = new char[3];
	buffread1 = 0;
	buffread2 = 0;
	buffread3 = 0;*/
}

Auto::~Auto(){ //Destructor
	/*delete duino;
	delete buff;*/
	delete powerPanel;
}

void Auto::AutoInitialize(){ //Initializes autonomous variables
	/*ingear = false;
	backedup = false;*/
	baselineReached = false;
	shotBalls = false;
	gearPlaced = false;
	jamCycles = 0;
	unjamCycles = 0;
}

/*void Auto::AutonRun(bool gear, bool ball, bool sensor){ //A messy function that will be removed
	duino->Read(buff, 3);
	buffread1 = (int) buff[0];
	buffread2 = (int) buff[1];
	buffread3 = (int) buff[2];
	double visDist = buffread1;
	double x1 = buffread2;
	double x2 = buffread3;
	double targetDistInch = 11;
	if(gear == true){
		if(sensor == true){
			if(ingear == false){
				if(visDist <= 0){
					drv->TankControllerDrive(0.0, 0.0);
				}
				else{
					if(visDist > (targetDistInch+2) && visDist < 70){
						if(x1-2 > x2+2){
							drv->TankControllerDrive(-0.25, -0.15);
						}
						else if(x2-2 > x1+2){
							drv->TankControllerDrive(-0.15, -0.25);
						}
						else{
							drv->TankControllerDrive(-0.25, -0.25);
						}
					}
					else if(visDist >= (targetDistInch - 2) && visDist <= (targetDistInch + 2)){
						drv->TankControllerDrive(0.0, 0.0);
						if(x2-2 > x1+2){
							drv->TankControllerDrive(0.15, -0.15);
						}
						else if(x1-2 > x2+2){
							drv->TankControllerDrive(-0.15, 0.15);
						}
						else{
							drv->TankControllerDrive(0.0, 0.0);
							ingear = true;
						}
					}
					else if (visDist < (targetDistInch-2) && visDist > 5){
						drv->TankControllerDrive(0.25, 0.25);
					}
					else{
						drv->TankControllerDrive(0.0, 0.0);
					}
				}
				SmartDashboard::PutNumber("VisDist: ", visDist);
				SmartDashboard::PutNumber("x1: ", buffread2);
				SmartDashboard::PutNumber("x2: ", buffread3);
			}
			else{
				drv->TankControllerDrive(0.0, 0.0);
				if(pDetect1->Get()){
					drv->TankControllerDrive(0.0, 0.0);
					gr->openClaw();
					Wait(0.75);
					gr->lowerClaw();
					if(!backedup){
						drv->TimeStraightDrive(0.25, 0.35);
						backedup = true;
					}
				}
				else{
					drv->TankControllerDrive(0.0, 0.0);
				}

				gr->openClaw();
				Wait(0.75);
				gr->lowerClaw();
				if(!backedup){
					drv->TimeStraightDrive(0.25, 0.35);
					backedup = true;
				}

				if(ball && !ballDone){
					drv->TimeStraightDrive(0.5, 1.0);
					Wait(0.5);
					//sht->SpinSequence(5000, 1.0, 0.5, 1.0, 7.0);
					Wait(0.5);
					ballDone = true;
				}
				else{
					drv->TankControllerDrive(0.0, 0.0);
				}
			}
		}
		else{
			if(ingear == false){
				drv->TimeStraightDrive(-0.5, 0.75);
				Wait(0.5);
				gr->openClaw();
				Wait(0.75);
				gr->lowerClaw();
				Wait(0.75);
				drv->TimeStraightDrive(0.25, 0.5);
				ingear = true;
			}
			else{
				drv->TankControllerDrive(0.0, 0.0);
			}
		}
	}

	else{
		drv->TimeStraightDrive(-0.3, 0.2);
	}
}*/

void Auto::BaselineAuto(){ //Autonomous to just reach the baseline and stop. The basis of any nutritious auto!
	if(!baselineReached){ //Preventing looping in periodic
		drv->TimeStraightDrive(baselineDrivePow, baselineDriveSecs);
		baselineReached = true;
	}
}

void Auto::BaselineGyroAuto(){ //Autonomous to just reach the baseline and stop. Now with gyro!
	if(!baselineReached){ //Preventing looping in periodic
		drv->TimeStraightGyroDrive(baselineDrivePow, baselineDriveSecs);
		baselineReached = true;
	}
}

void Auto::BallAuto(Auto::shooterPowMode shootPower){ //Shoots balls and reaches baseline
	int shootingCycles = shootCycles;
	if(!shotBalls && shootPower != kNoPow){ //Preventing looping in periodic
		for(int i = 0; i < shooterSpinupCycles; i++){
			if(shootPower == kLowPow){
				sht->SpinShootEncoder(lowAutoShootRPM);
			}
			else if(shootPower == kHighPow){
				sht->SpinShootEncoder(highAutoShootRPM);
			}
			else{
				sht->SpinShootEncoder(midAutoShootRPM);
			}
			Wait(centisecond);
		}
		for(int i = 0; i < shootingCycles; i++){
			if(shootPower == kLowPow){
				sht->SpinShootEncoder(lowAutoShootRPM);
				shootingCycles = 700;
			}
			else if(shootPower == kHighPow){
				sht->SpinShootEncoder(highAutoShootRPM);
				shootingCycles = 700;
			}
			else{
				sht->SpinShootEncoder(midAutoShootRPM);
				shootingCycles = shootCycles;
			}
			sht->SpinFeed(feedPow);
			sht->SpinMeter(meterPow);
			if(powerPanel->GetCurrent(feederPDPID) > feedStallCurrent){
				jamCycles++;
				if(jamCycles >= feedJamCycles){
					sht->SpinFeed(-feedPow);
					unjamCycles++;
					if(unjamCycles >= feedUnjamCycles){
						jamCycles = 0;
						unjamCycles = 0;
					}
				}
			}
			Wait(centisecond);
		}
		shotBalls = true;
		Wait(halfSecond);
	}
	sht->SpinShootEncoder(STOP);
	sht->SpinMeter(STOP);
	sht->SpinFeed(STOP);
}

void Auto::GearAuto(Auto::AutoPosition position){ //Places a gear on the peg
	Wait(halfSecond);
	if(!gearPlaced){ //Preventing looping in periodic
		if(position == kLeftAuto){
			BaselineAuto();
			gearPlaced = true;
		}
		else if(position == kRightAuto){
			BaselineAuto();
			gearPlaced = true;
		}
		else{
			BaselineGyroAuto();
			gr->openClaw();
			Wait(halfSecond);
			gr->lowerClaw();
			drv->TimeStraightDrive(afterGearBackDrivePow, halfSecond);
			gearPlaced = true;
		}
	}
}

void Auto::GearVisionAuto(Auto::AutoPosition position){ //Vision-based GearAuto

}

void Auto::BallGearAuto(Auto::AutoPosition position, Auto::shooterPowMode shootPower){ //Shoots balls then places a gear
	if(position == kLeftAuto){
		BallAuto(shootPower);
		BaselineAuto();
	}
	else if(position == kRightAuto){
		BallAuto(shootPower);
		BaselineAuto();
	}
	else{
		BallAuto(shootPower);
		BaselineGyroAuto();
		Wait(halfSecond);
		if(!gearPlaced){ //Preventing looping in periodic
			gr->openClaw();
			Wait(halfSecond);
			gr->lowerClaw();
			drv->TimeStraightDrive(afterGearBackDrivePow, halfSecond);
			gearPlaced = true;
		}
	}
}

void Auto::BallGearVisionAuto(Auto::AutoPosition position){ //Vision-based BallGearAuto

}

void Auto::GearBallAuto(Auto::AutoPosition position, Auto::shooterPowMode shootPower){ //Places a gear, drives back, then shoots balls
	if(!gearPlaced){ //Preventing looping in periodic
		if(position == kLeftAuto){
			BallAuto(shootPower);
			BaselineAuto();
		}
		else if(position == kRightAuto){
			BallAuto(shootPower);
			BaselineAuto();
		}
		else{
			GearAuto(position);
			if(!shotBalls && shootPower != kNoPow){ //Preventing looping in periodic
				drv->TimeStraightDrive(afterGearBackDrivePow, second);
				Wait(0.5);
				for(int i = 0; i < shooterSpinupCycles; i++){
					if(shootPower == kLowPow){
						sht->SpinShootEncoder(lowAutoShootRPM);
					}
					else if(shootPower == kHighPow){
						sht->SpinShootEncoder(highAutoShootRPM);
					}
					else{
						sht->SpinShootEncoder(midAutoShootRPM);
					}
					Wait(centisecond);
				}
				for(int i = 0; i < shootCycles; i++){
					if(shootPower == kLowPow){
						sht->SpinShootEncoder(lowAutoShootRPM);
					}
					else if(shootPower == kHighPow){
						sht->SpinShootEncoder(highAutoShootRPM);
					}
					else{
						sht->SpinShootEncoder(midAutoShootRPM);
					}
					sht->SpinFeed(feedPow);
					sht->SpinMeter(meterPow);
					if(powerPanel->GetCurrent(feederPDPID) > feedStallCurrent){
						jamCycles++;
						if(jamCycles >= feedJamCycles){
							sht->SpinFeed(-feedPow);
							unjamCycles++;
							if(unjamCycles >= feedUnjamCycles){
								jamCycles = 0;
								unjamCycles = 0;
							}
						}
					}
					Wait(centisecond);
				}
				shotBalls = true;
				Wait(halfSecond);
			}
			sht->SpinShootEncoder(STOP);
			sht->SpinMeter(STOP);
			sht->SpinFeed(STOP);
		}
	}
}

void Auto::GearBallVsionAuto(Auto::AutoPosition position){ //Vision-based GearBallAuto

}
