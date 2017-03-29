/*
 * ClimbSystem.h
 *
 *  Created on: Feb 17, 2017
 *      Author: 4810
 */

#ifndef SRC_SYSTEMS_CLIMBSYSTEM_CLIMBSYSTEM_H_
#define SRC_SYSTEMS_CLIMBSYSTEM_CLIMBSYSTEM_H_

#include <CANTalon.h>

class ClimbSystem{

public:
	ClimbSystem(CANTalon* climb1Talon, CANTalon* climb2Talon);
	~ClimbSystem();

	CANTalon* clmb1Tl;
	CANTalon* clmb2Tl;

	void Climb(double speed);

private:

protected:

};

#endif /* SRC_SYSTEMS_CLIMBSYSTEM_CLIMBSYSTEM_H_ */
