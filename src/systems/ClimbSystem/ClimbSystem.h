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
	ClimbSystem(CANTalon* climbTalon, CANTalon* leftIntakeTalon, CANTalon* rightIntakeTalon);
	~ClimbSystem();

	CANTalon* clmbTl;
	CANTalon* rInTal;
	CANTalon* lInTal;

	void IntakeRope(double speed);
	void Climb(double speed);
	void Home(double pos);

private:

protected:

};

#endif /* SRC_SYSTEMS_CLIMBSYSTEM_CLIMBSYSTEM_H_ */
