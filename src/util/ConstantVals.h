/*
 * Constants.h
 *
 *  Created on: Feb 10, 2017
 *      Author: 4810
 *
 * Constant values used in 2017 robot.
 */

//Header guards
#ifndef SRC_UTIL_CONSTANTVALS_H_
#define SRC_UTIL_CONSTANTVALS_H_

//General
const double STOP = 0.0;
const double ZERO = 0.0;

//Controls
const double stickDeadband = 0.25;
const double stickOutSlope = 1;
const double stickOutIntercept = -0.25;
const double turnStickOutSlope = 0.6;
const double turnStickOutIntercept = -0.15;
const double trigDeadband = 0.0;
const double trigOutSlope = 1.0;
const double trigOutIntercept = 0.0;

//Drive
const double wheelDiameter = 4.0;
const int encoderRotationCounts = 1024;

//Shooter
const double shootDivisor = 0.7;
const double shootPowFactor = 0.25;

//Auto
const double lowAutoShootRPM = 5550;
const double midAutoShootRPM = 6450;
const double highAutoShootRPM = 9200;

#endif /* SRC_UTIL_CONSTANTVALS_H_ */
