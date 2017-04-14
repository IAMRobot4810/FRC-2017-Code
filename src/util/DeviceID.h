/*
 * DeviceID.h
 *
 *  Created on: Feb 10, 2017
 *      Author: 4810
 *
 * Device IDs for 2017 robot.
 */

//Header guards
#ifndef SRC_UTIL_DEVICEID_H_
#define SRC_UTIL_DEVICEID_H_

enum GeneralIDs {
	pdpID = 1,
	camera1ID = 0,
	camera2ID = 1,
	rLEDID = 0,
	gLEDID = 1,
	bLEDID = 2
};

enum ControllerIDs {
	controller1ID = 0,
	controller2ID = 1
};

enum DriveIDs {
	flTalID = 2, //3, //2
	rlTalID = 1, //5, //1
	frTalID = 4, //2, //4
	rrTalID = 5, //1,
	flEncID = 0,
	frEncID = 3,
};

enum ClimberIDs {
	roller1TalID = 9,
	roller2TalID = 8//4//8, //7
};

enum GearIDs {
	pcmID = 1,
	raiseNoidForwardID = 0,//3,
	raiseNoidReverseID = 1,//2,
	clawNoidForwardID = 2,//1,
	clawNoidReverseID = 3,//0
	gearSensorID = 0,
	pegSensorID = 1
};

enum ShootIDs {
	feederTalID = 3,//6,
	meterTalID = 6, //7,//7, //4
	shooterTalID = 7 //4
};

#endif /* SRC_UTIL_DEVICEID_H_ */
