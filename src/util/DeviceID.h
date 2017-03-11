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
	rLEDID = 0,
	gLEDID = 1,
	bLEDID = 2
};

enum ControllerIDs {
	controller1ID = 0,
	controller2ID = 1
};

enum DriveIDs {
	flTalID = 5,
	rlTalID = 3,
	frTalID = 2,
	rrTalID = 1,
	flEncID = 0,
	frEncID = 3,
	gyroID
};

enum ClimberIDs {
	rollerTalID = 9,
	intake1TalID = 7,
	intake2TalID = 8
};

enum GearIDs {
	pcmID = 1,
	raiseNoidForwardID = 0,
	raiseNoidReverseID = 1,
	clawNoidForwardID = 2,
	clawNoidReverseID = 3
};

enum BallIDs {
	ballPick1TalID = 6,
	ballPick2TalID = 4,
	ballSolForwardID = 4,
	ballSolReverseID = 5
};

#endif /* SRC_UTIL_DEVICEID_H_ */
