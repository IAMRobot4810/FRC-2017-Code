/*
 * DeviceID.h
 *
 *  Created on: Feb 10, 2017
 *      Author: 4810
 */

#ifndef SRC_UTIL_DEVICEID_H_
#define SRC_UTIL_DEVICEID_H_

enum GeneralIDs {
	gearSensorID = 0, //0
	pegSensor1ID = 1, //1
	pegSensor2ID = 2,
	camera1ID = 0,
	rLEDID = 0,
	gLEDID = 1,
	bLEDID = 2
};

enum ControllerIDs {
	controller1ID = 0,
	controller2ID = 1
};

enum DriveIDs {
	flTalID = 2, //5
	rlTalID = 1, //3
	frTalID = 4, //2
	rrTalID = 5, //1
	flEncID = 0,
	frEncID = 3,
	gyroID
};

enum ClimberIDs {
	roller1TalID = 9,
	roller2TalID = 8, //7
};

enum GearIDs {
	pcmID = 1,
	raiseNoidForwardID = 3, //0
	raiseNoidReverseID = 2, //1
	clawNoidForwardID = 1, //2
	clawNoidReverseID = 0 //3
};

enum ShootIDs {
	feederTalID = 6,
	meterTalID = 7, //4
	shooterTalID = 3 //4
};

#endif /* SRC_UTIL_DEVICEID_H_ */
