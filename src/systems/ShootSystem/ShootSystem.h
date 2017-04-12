/*
 * BallSystem.h
 *
 *  Created on: Feb 17, 2017
 *      Author: 4810
 */

#ifndef SRC_SYSTEMS_SHOOTSYSTEM_SHOOTSYSTEM_H_
#define SRC_SYSTEMS_SHOOTSYSTEM_SHOOTSYSTEM_H_

#include <CANTalon.h>
#include <DoubleSolenoid.h>
#include <PowerDistributionPanel.h>
#include <Timer.h>
#include <util/DeviceID.h>
#include <util/ConstantVals.h>
#include <cmath>

using namespace frc;

class ShootSystem{

public:
	ShootSystem(CANTalon* feederTalon, CANTalon* meterTalon, CANTalon* shootTalon);
	~ShootSystem();

	CANTalon* bfeed;
	CANTalon* bmeter;
	CANTalon* bshoot;

	void SpinShoot(double speed);
	void SpinMeter(double speed);
	void SpinFeed(double speed);
	void UnjamFeed(double speed);
	void SpinSequence(double shootSpeed, double meterSpeed, double feedSpeed, double spinTime, double shootTime);
	void SpinSequenceCalibrated(double shootSpeed, double meterSpeed, double feedSpeed, double spinTime, double shootTime, double threshold, double power);
	void SpinSequenceVoltage(double shootSpeed, double meterSpeed, double feedSpeed, double spinTime, double shootTime, double threshold, double power);
	void SpinSequenceMod(double shootSpeed, double meterSpeed, double feedSpeed, double spinTime, double shootTime);
private:

protected:

};

#endif /* SRC_SYSTEMS_SHOOTSYSTEM_SHOOTSYSTEM_H_ */
