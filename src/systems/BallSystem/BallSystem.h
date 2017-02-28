/*
 * BallSystem.h
 *
 *  Created on: Feb 17, 2017
 *      Author: 4810
 */

#ifndef SRC_SYSTEMS_BALLSYSTEM_BALLSYSTEM_H_
#define SRC_SYSTEMS_BALLSYSTEM_BALLSYSTEM_H_

#include <CANTalon.h>
#include <DoubleSolenoid.h>

using namespace frc;

class BallSystem{

public:
	BallSystem(CANTalon* outerWallTalon, CANTalon* innerWallTalon, DoubleSolenoid* wallSolenoid);
	~BallSystem();

	CANTalon* b1Tl;
	CANTalon* b2Tl;
	DoubleSolenoid* blSl;

	bool wallRaised;

	void SpinPickup(double speed);
	void RaiseWall();
	void LowerWall();

private:

protected:

};

#endif /* SRC_SYSTEMS_BALLSYSTEM_BALLSYSTEM_H_ */
