/*
 * Auto.cpp
 *
 *  Created on: Feb 21, 2017
 *      Author: 4810
 */

#include <auto/Auto.h>

Auto::Auto(DriveSystem* driveSystem, GearSystem* gearSystem, DigitalInput* gearDetectSensor,
		DigitalInput* pegDetectSensor1, ShootSystem* shootSystem){
	drv = driveSystem;
	gr = gearSystem;
	gDetect = gearDetectSensor;
	pDetect1 = pegDetectSensor1;
	sht = shootSystem;

	duino = new SerialPort(9600, SerialPort::kUSB1);
	buff = new char[3];
	buffread1 = 0;
	buffread2 = 0;
	buffread3 = 0;
}

Auto::~Auto(){
	delete duino;
	delete buff;
}

void Auto::AutoInitialize(bool ball){
	if(ball){
		sht->SpinSequence(5000, 1.0, 0.5, 1.0);
		Wait(0.5);
		drv->TimeStraightDrive(-0.5, 1.25);
		ingear = false;
	}
	else{
		drv->TimeStraightDrive(-0.5, 1.25);
		ingear = false;
	}
}
void Auto::AutonRun(bool gear, bool sensor){
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
