#ifndef IDS
#define IDS
enum DriveID{
	flTalID = 1,
	frTalID = 3,
	rlTalID = 2,
	rrTalID = 4,
	mainControllerID = 0,
};

enum SensorID{
	flEncID1,
	flEncID2,
	frEncID1,
	frEncID2,
	gyroID,
	BannerID = 0

};

enum PnuematicIDS{
	liftSolenoidID = 0,
	clampSolenoidID = 1,
	PCM_ID = 1
};

enum BallPickup{
	innerRollerID,
	outerRollerID,
	backDoorID
};


#endif
