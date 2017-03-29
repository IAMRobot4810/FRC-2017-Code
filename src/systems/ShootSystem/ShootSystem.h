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
#include <Timer.h>

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
	void SpinSequence(double shootSpeed, double meterSpeed, double feedSpeed, double spinTime);

private:

protected:

};

#endif /* SRC_SYSTEMS_SHOOTSYSTEM_SHOOTSYSTEM_H_ */
