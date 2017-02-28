/*
 * DriveSystem.h
 *
 *  Created on: Feb 10, 2017
 *      Author: 4810
 */

#ifndef SRC_SYSTEMS_DRIVESYSTEM_DRIVESYSTEM_H_
#define SRC_SYSTEMS_DRIVESYSTEM_DRIVESYSTEM_H_

#include <CANTalon.h>
#include <RobotDrive.h>
#include <AnalogGyro.h>
#include <PWM.h>
#include <util/DeviceID.h>
#include <Timer.h>
#include <cmath>
#include <util/ConstantVals.h>

using namespace frc;

class DriveSystem {

public:
	DriveSystem(RobotDrive* roboDrive, PWM* leftEncoder, PWM* rightEncoder, AnalogGyro* gyro);
	~DriveSystem();

	RobotDrive* drov;
	AnalogGyro* gyr;
	PWM* flE;
	PWM* frE;

	void TankControllerDrive(double leftSpeed, double rightSpeed);
	void ArcadeControllerDrive(double moveSpeed, double turnSpeed);
	void TimeStraightDrive(double driveSpeed, double driveSeconds);
	double EncoderScale(int encoderReading, double wheelDiameterInches);
	void DistanceStraightDrive(double positiveDriveSpeed, double driveFeet);
	void RotateDrive(double positiveDriveSpeed, double driveDegrees, bool reInitializeGyro);

private:

protected:

};

#endif /* SRC_SYSTEMS_DRIVESYSTEM_DRIVESYSTEM_H_ */
