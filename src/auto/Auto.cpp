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

	//Vision stuff with PixyCam
	duino = new SerialPort(9600, SerialPort::kUSB1);
	buff = new char[3];
	buffread1 = 0;
	buffread2 = 0;
	buffread3 = 0;
}

Auto::~Auto(){ //Destructor
	delete duino;
	delete buff;
}

void Auto::AutoInitialize(){ //Initializes autonomous variables
	ingear = false;
	backedup = false;
	baselineReached = false;
	shotBalls = false;
	gearPlaced = false;
}

void Auto::AutonRun(bool gear, bool ball, bool sensor){ //A messy function that will be removed
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
					sht->SpinSequence(5000, 1.0, 0.5, 1.0, 7.0);
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
}

void Auto::BaselineAuto(){ //Autonomous to just reach the baseline and stop
	if(!baselineReached){ //Preventing looping in periodic
		drv->TimeStraightDrive(-0.3, 2.5);
		baselineReached = true;
	}
}

void Auto::BallAuto(Auto::shooterPowMode power){ //Shoots balls and reaches baseline
	if(!shotBalls){ //Preventing looping in periodic
		if(power == kMidPow){
			sht->SpinSequence(0.8, 1.5, 0.5, 1.0, 7.0);
			shotBalls = true;
			Wait(0.5);
		}
		else if(power == kHighPow){
			sht->SpinSequence(1.0, 1.5, 0.5, 1.0, 7.0);
			shotBalls = true;
			Wait(0.5);
		}
		else{
			sht->SpinSequence(0.52, 1.5, 0.5, 1.0, 7.0);
			shotBalls = true;
			Wait(0.5);
		}
	}
	else{
		BaselineAuto();
	}
}

void Auto::GearAuto(Auto::AutoPosition position){ //Places a gear on the peg
	BaselineAuto();
	Wait(0.5);
	if(!gearPlaced){ //Preventing looping in periodic
		if(position == kLeftAuto){

		}
		else if(position == kRightAuto){

		}
		else{
			gr->openClaw();
			Wait(0.5);
			gr->lowerClaw();
			drv->TimeStraightDrive(0.25, 0.5);
		}
	}
}

void Auto::GearVisionAuto(Auto::AutoPosition position){ //Vision-based GearAuto

}

void Auto::BallGearAuto(Auto::AutoPosition position){ //Shoots balls then places a gear
	if(position == kLeftAuto){
		if(!shotBalls){ //Preventing looping in periodic
			sht->SpinSequence(0.5, 1.0, 0.5, 1.0, 5.5);
			shotBalls = true;
			Wait(0.5);
		}
	}
	else if(position == kRightAuto){
		if(!shotBalls){ //Preventing looping in periodic
			sht->SpinSequence(1.0, 1.0, 0.5, 1.0, 5.5);
			shotBalls = true;
			Wait(0.5);
		}
	}
	else{
		if(!shotBalls){ //Preventing looping in periodic
			sht->SpinSequence(0.8, 1.0, 0.5, 1.0, 5.5);
			shotBalls = true;
			Wait(0.5);
		}
		BaselineAuto();
		Wait(0.5);
		if(!gearPlaced){ //Preventing looping in periodic
			gr->openClaw();
			Wait(0.5);
			gr->lowerClaw();
			drv->TimeStraightDrive(0.3, 2.5);
			gearPlaced = true;
		}
	}
}

void Auto::BallGearVisionAuto(Auto::AutoPosition position){ //Vision-based BallGearAuto

}

void Auto::GearBallAuto(Auto::AutoPosition position){ //Places a gear, drives back, then shoots balls
	if(!gearPlaced){ //Preventing looping in periodic
		if(position == kLeftAuto){

		}
		else if(position == kRightAuto){

		}
		else{
			BaselineAuto();
			Wait(0.5);
			gr->openClaw();
			Wait(0.5);
			gr->lowerClaw();
			drv->TimeStraightDrive(0.3, 2.5);
			Wait(0.5);
			if(!shotBalls){ //Preventing looping in periodic
				sht->SpinSequence(0.8, 1.0, 0.5, 1.0, 3.5);
				shotBalls = true;
			}
		}
	}
}

void Auto::GearBallVsionAuto(Auto::AutoPosition position){ //Vision-based GearBallAuto

}
