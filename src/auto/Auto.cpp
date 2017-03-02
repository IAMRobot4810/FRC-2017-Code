/*
 * Auto.cpp
 *
 *  Created on: Feb 21, 2017
 *      Author: 4810
 */

#include <auto/Auto.h>

Auto::Auto(DriveSystem* driveSystem, GearSystem* gearSystem, DigitalInput* gearDetectSensor,
		DigitalInput* pegDetectSensor){
	drv = driveSystem;
	gr = gearSystem;
	gDetect = gearDetectSensor;
	pDetect = pegDetectSensor;
}

Auto::~Auto(){

}

void Auto::AutonRun(bool sensors){
	if(sensors == true){
		//drv->DistanceStraightDrive(0.75, 9.5);
		drv->TimeStraightDrive(-0.5, 5.0);
		//gr->openClaw();
	}
	else{
	}
}
