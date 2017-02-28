/*
 * GearSystem.h
 *
 *  Created on: Feb 12, 2017
 *      Author: 4810
 */

#ifndef SRC_SYSTEMS_GEARSYSTEM_GEARSYSTEM_H_
#define SRC_SYSTEMS_GEARSYSTEM_GEARSYSTEM_H_

#include <DoubleSolenoid.h>
#include <SmartDashboard/SmartDashboard.h>
#include <DigitalInput.h>
#include <util/DeviceID.h>

using namespace frc;

class GearSystem {

public:
	GearSystem(DoubleSolenoid* liftSolenoid, DoubleSolenoid* clawSolenoid);
	~GearSystem();

	bool raised;
	bool open;

	DoubleSolenoid* liftNoid;
	DoubleSolenoid* clawNoid;

	void raiseClaw();
	void lowerClaw();
	void openClaw();
	void closeClaw();

private:

protected:

};

#endif /* SRC_SYSTEMS_GEARSYSTEM_GEARSYSTEM_H_ */
