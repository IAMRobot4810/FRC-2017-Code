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

//Timer
const double decisecond = 0.1;
const double centisecond = 0.01;
const double millisecond = 0.001;
const double halfSecond = 0.5;
const double threeQuarterSecond = 0.75;
const double second = 1.0;

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
const double feedPow = 0.5;
const double meterPow = 1.0;

//Auto
const double baselineDrivePow = -1.0;
const double baselineDriveSecs = 0.6;
const int shooterSpinupCycles = 25;
const int shootCycles = 300;
const double feedStallCurrent = 9.0;
const int feedJamCycles = 50;
const int feedUnjamCycles = 50;
const double afterGearBackDrivePow = 0.5;
const double lowAutoShootRPM = 5550;
const double midAutoShootRPM = 6450;
const double highAutoShootRPM = 9200;

#endif /* SRC_UTIL_CONSTANTVALS_H_ */
