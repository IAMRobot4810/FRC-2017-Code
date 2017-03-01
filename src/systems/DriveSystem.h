/*
 * DriveSystem.h
 *
 *  Created on: Feb 10, 2017
 *      Author: Anish
 */

#ifndef SRC_SYSTEMS_DRIVESYSTEM_H_
#define SRC_SYSTEMS_DRIVESYSTEM_H_
#include "WPILib.h"
#include "CANTalon.h"
#include "teleop/controls/Deadband.h"
#include "util/DeviceIDs.h"
#include "systems/Constants.h"
using namespace frc;

class DriveSystem {
public:
	virtual ~DriveSystem();
	CANTalon *flTalon;
	CANTalon *frTalon;
	CANTalon *rlTalon;
	CANTalon *rrTalon;
	RobotDrive *drive;
	Encoder* driveEncoder1;
	Encoder* driveEncoder2;
	XboxController* controller;
	DriveSystem(XboxController* mainController);
	void DriveArcade();
	void AnishArcadeDrive();
	void AnishArcadeDriveSquare();
	void ArcadeDriveStick();
	void ArcadeDriveStickSquare();
	void TankDriveStick();
	void TankDriveStickSquare();
	Deadband* driveband;
//private:


};

#endif /* SRC_SYSTEMS_DRIVESYSTEM_H_ */
