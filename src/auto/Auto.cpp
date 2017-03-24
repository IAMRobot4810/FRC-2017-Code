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
}

Auto::~Auto(){

}

void Auto::AutonRun(bool gear){
	if(gear == true){
		//drv->DistanceStraightDrive(0.75, 9.5);
		drv->TimeStraightDrive(-0.3, 2.25);
		Wait(0.5);
		if(pDetect1->Get() || pDetect2->Get()){
			gr->openClaw();
		}
		//gr->openClaw();
		Wait(0.5);
		drv->TimeStraightDrive(0.3, 0.75);
	}
	else{
		drv->TimeStraightDrive(-0.3, 0.2);
	}
}
