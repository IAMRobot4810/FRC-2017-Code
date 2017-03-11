/*
 * Auto.h
 *
 *  Created on: Feb 21, 2017
 *      Author: 4810
 */

#ifndef SRC_AUTO_AUTO_H_
#define SRC_AUTO_AUTO_H_

#include <systems/DriveSystem/DriveSystem.h>
#include <systems/GearSystem/GearSystem.h>
#include <DigitalInput.h>

class Auto {

public:
	Auto(DriveSystem* driveSystem, GearSystem* gearSystem, DigitalInput* gearDetectSensor,
			DigitalInput* pegDetectSensor1, DigitalInput* pegDetectSensor2);
	~Auto();

	void AutonRun(bool gear);

private:
	DriveSystem* drv;
	GearSystem* gr;
	DigitalInput* gDetect;
	DigitalInput* pDetect1;
	DigitalInput* pDetect2;

protected:

};

#endif /* SRC_AUTO_AUTO_H_ */
