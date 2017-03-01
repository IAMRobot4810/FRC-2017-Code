/*
 * Deadband.h
 *
 *  Created on: Feb 11, 2017
 *      Author: Anish
 */

#ifndef SRC_TELEOP_CONTROLS_DEADBAND_H_
#define SRC_TELEOP_CONTROLS_DEADBAND_H_

class Deadband {
public:
	Deadband(double LowBound, double HighBound);
	double ReturnBoundedValue(double value);
	double LowBound;
	double HighBound;


};

#endif /* SRC_TELEOP_CONTROLS_DEADBAND_H_ */
