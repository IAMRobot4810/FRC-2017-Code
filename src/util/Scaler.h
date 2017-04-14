/*
 * Scale.h
 *
 *  Created on: Feb 13, 2017
 *      Author: 4810
 *
 * Class with various scaling functions for sticks, triggers etc.
 */

//Header guards
#ifndef SRC_UTIL_SCALER_H_
#define SRC_UTIL_SCALER_H_

//Includes
#include <cmath>
#include <util/Constantvals.h>

class Scaler { //Creating class "Scaler"

public:
	Scaler(); //Constructor
	~Scaler(); //Destructor

	//Pretty self-explanatory
	double ExponentialScale(double input, double minIn, double maxIn,
			double minOut, double maxOut, double exponent);
	double LinearScale(double input, double m, double b, bool negativeOpposite);
	double autoLinearScale(double in, double minIn, double maxIn, double minOut, double maxOut);
	double exponentialScale(double in, int exp, double multiple, double intercept, bool negativesOpposite);
	double autoExponentialScale(double in, double minIn, double maxIn, double minOut, double maxOut, double power);

private:

protected:

};

#endif /* SRC_UTIL_SCALER_H_ */
