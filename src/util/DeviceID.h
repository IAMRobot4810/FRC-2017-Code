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
	pegSensorID = 1,
	camera1ID
};

enum ControllerIDs {
	controller1ID = 0,
	controller2ID = 1
};

enum DriveIDs {
	flTalID = 1,
	rlTalID = 2,
	frTalID = 4,
	rrTalID = 5,
	flEncID = 0,
	frEncID = 3,
	gyroID
};

enum ClimberIDs {
	rollerTalID = 3,
	intake1TalID = 7,
	intake2TalID = 6
};

enum GearIDs {
	pcmID = 1,
	raiseNoidForwardID = 0,
	raiseNoidReverseID = 1,
	clawNoidForwardID = 2,
	clawNoidReverseID = 3
};

enum BallIDs {
	ballPick1TalID = 9,
	ballPick2TalID = 8,
	ballSolForwardID = 4,
	ballSolReverseID = 5
};

#endif /* SRC_UTIL_DEVICEID_H_ */
