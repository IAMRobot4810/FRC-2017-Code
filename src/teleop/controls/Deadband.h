/*
 * Deadband.h
 *
 *  Created on: Feb 13, 2017
 *      Author: 4810
 */

#ifndef SRC_TELEOP_CONTROLS_DEADBAND_H_
#define SRC_TELEOP_CONTROLS_DEADBAND_H_

class Deadband {

public:
	Deadband();
	~Deadband();

	double DeadbandOut(double input, double deadBandLimit);

private:

protected:

};

#endif /* SRC_TELEOP_CONTROLS_DEADBAND_H_ */
