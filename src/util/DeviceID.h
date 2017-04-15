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
	gyroID = 1
};

enum ControllerIDs {
	controller1ID = 0,
	controller2ID = 1
};

enum DriveIDs {
	flTalID = 3,
	rlTalID = 5,
	frTalID = 2,
	rrTalID = 1
};

enum ClimberIDs {
	roller1TalID = 4,
	roller2TalID = 9
};

enum GearIDs {
	pcmID = 1,
	raiseNoidForwardID = 0,
	raiseNoidReverseID = 1,
	clawNoidForwardID = 2,
	clawNoidReverseID = 3,
	gearSensorID = 0,
	pegSensorID = 1
};

enum ShootIDs {
	feederTalID = 8,
	feederPDPID = 1,
	meterTalID = 7,
	shooterTalID = 6
};

#endif /* SRC_UTIL_DEVICEID_H_ */
