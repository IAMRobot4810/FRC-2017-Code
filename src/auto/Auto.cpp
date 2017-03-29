/*
 * Auto.cpp
 *
 *  Created on: Feb 21, 2017
 *      Author: 4810
 */

#include <auto/Auto.h>

Auto::Auto(DriveSystem* driveSystem, GearSystem* gearSystem, DigitalInput* gearDetectSensor,
		DigitalInput* pegDetectSensor1, DigitalInput* pegDetectSensor2){
	drv = driveSystem;
	gr = gearSystem;
	gDetect = gearDetectSensor;
	pDetect1 = pegDetectSensor1;
	pDetect2 = pegDetectSensor2;

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

void Auto::AutoInitialize(){
	drv->TimeStraightDrive(-0.5, 1.0);
	ingear = false;
}
void Auto::AutonRun(bool gear){
	duino->Read(buff, 3);
	buffread1 = (int) buff[0];
	buffread2 = (int) buff[1];
	buffread3 = (int) buff[2];
	double visDist = buffread1;
	double x1 = buffread2;
	double x2 = buffread3;
	double targetDistInch = 16;
	if(gear == true){
		//drv->DistanceStraightDrive(0.75, 9.5);
		/*drv->TimeStraightDrive(-0.3, 2.25);
		Wait(0.5);
		if(pDetect1->Get() || pDetect2->Get()){
			gr->openClaw();
		}
		//gr->openClaw();
		Wait(0.5);
		drv->TimeStraightDrive(0.3, 0.75);*/
		if(ingear == false){

		if(visDist <= 0){
			drv->TankControllerDrive(0.0, 0.0);
		}
		else{
			if(visDist > (targetDistInch+2)){
				if(x1 > x2){
					drv->TankControllerDrive(-0.25, -0.15);
				}
				else if(x2 > x1){
					drv->TankControllerDrive(-0.15, -0.25);
				}
				else{
					drv->TankControllerDrive(-0.25, -0.25);
				}
				//drive->TankDrive(-driveSpeed, -driveSpeed, false);
			}
			else if(visDist >= (targetDistInch - 2) && visDist <= (targetDistInch + 2)){
				drv->TankControllerDrive(0.0, 0.0);
				if(x1 < x2){
					drv->TankControllerDrive(0.15, -0.15);
				}
				else if(x2 < x1){
					drv->TankControllerDrive(-0.15, 0.15);
				}
				else{
					drv->TankControllerDrive(0.0, 0.0);
					ingear = true;
				}
			}
			else if (visDist < (targetDistInch-2)){
				drv->TankControllerDrive(0.25, 0.25);
			}
			else{
				drv->TankControllerDrive(0.0, 0.0);
			}
		}
		SmartDashboard::PutNumber("VisDist: ", visDist);
		//SmartDashboard::PutNumber("VisDistFromHeight", buffread2);
		SmartDashboard::PutNumber("x1: ", buffread2);
		SmartDashboard::PutNumber("x2: ", buffread3);
		}
		else{
			drv->TankControllerDrive(0.0, 0.0);
			gr->openClaw();
			Wait(1.0);
			gr->lowerClaw();
		}
	}
	else{
		drv->TimeStraightDrive(-0.3, 0.2);
	}
}
