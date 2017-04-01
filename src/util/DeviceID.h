/*
 * DeviceID.h
 *
 *  Created on: Feb 10, 2017
 *      Author: 4810
 */

#ifndef SRC_UTIL_DEVICEID_H_
#define SRC_UTIL_DEVICEID_H_

enum GeneralIDs {
	gearSensorID = 0,
	pegSensor1ID = 1,
	pegSensor2ID = 2,
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
	flTalID = 3, //2
	rlTalID = 5, //1
	frTalID = 2, //4
	rrTalID = 1, //5
	flEncID = 0,
	frEncID = 3,
	gyroID
};

enum ClimberIDs {
	roller1TalID = 9,
	roller2TalID = 4//8, //7
};

enum GearIDs {
	pcmID = 1,
	raiseNoidForwardID = 0,//3,
	raiseNoidReverseID = 1,//2,
	clawNoidForwardID = 2,//1,
	clawNoidReverseID = 3,//0
};

enum ShootIDs {
	feederTalID = 8,//6,
	meterTalID = 7,//7, //4
	shooterTalID = 6 //4
};

#endif /* SRC_UTIL_DEVICEID_H_ */
