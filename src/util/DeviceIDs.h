#ifndef IDS
#define IDS

enum DriveID{
	flTalID = 1,
	frTalID = 4,
	rlTalID = 2,
	rrTalID = 5,
	mainControllerID = 0,
	auxID
};

enum SensorID{
	flEncID1,
	flEncID2,
	frEncID1,
	frEncID2,
	gyroID,
	BannerID=0,
	cameraID


};

enum PnuematicIDS{
	liftSolenoidID1=0,
	liftSolenoidID2=1,
	clampSolenoidID1=2,
	clampSolenoidID2=3,
	PCM_ID=1
};

enum BallPickup{
	innerRollerID=9,
	outerRollerID=8,
	backDoorID1 = 4,
	backDoorID2 =5
};

enum LifterID{
	leftInRollerID=7,
	rightInRollerID=6,
	lifterTalonID=3

};

enum LED{
	rLEDID =0,
	bLEDID=2,
	gLEDID=1
};


#endif
